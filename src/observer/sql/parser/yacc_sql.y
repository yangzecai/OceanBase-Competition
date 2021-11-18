
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t id_list_length;
  size_t tuple_num;
  size_t string_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  char *id_list[MAX_NUM];
  SelectFrame select_frame[QUERY_NUM];
  int select_frame_index;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->id_list_length = 0;
  context->tuple_num = 0;
  context->string_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
        MAX
        MIN
        COUNT
        AVG
        INNER
        JOIN
        UNIQUE
        ORDER
        BY
        ASC
        GROUP
        NOT
        NULL_T
        NULLABLE_T
        IS

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;
%type <number> null_type;
%type <number> comOp
%type <number> agg_type;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE unique_index INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON
		{
            CONTEXT->id_list[0] = $8;
            CONTEXT->id_list_length++;
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, (const char**)CONTEXT->id_list, CONTEXT->id_list_length);
			CONTEXT->id_list_length = 0;
		}
    ;
unique_index:
    /* empty */
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
        }
    | UNIQUE
        {
            CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;//"create_unique_index";
        }
    ;
id_list:
    /* empty */
    | COMMA ID id_list  {
            CONTEXT->id_list_length++;
            CONTEXT->id_list[CONTEXT->id_list_length] = $2;
	  }
    ;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
			CONTEXT->tuple_num = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, NOT_NULL);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    | ID_get type null_type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, $3);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
    INT_T { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T { $$=FLOATS; }
    | DATE_T { $$=DATES; }
    | TEXT_T { $$=TEXTS; }
    ;
ID_get:
    ID
    {
      char *temp=$1; 
      snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
    ;
null_type:
    /* empty */ { $$=NOT_NULL; }
    | NULLABLE_T { $$=NULLABLE; }
    | NOT NULL_T { $$=NOT_NULL; }
    ;
	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE value_tuple SEMICOLON
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			CONTEXT->tuple_num++;
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length, CONTEXT->tuple_num);

      //临时变量清零
      CONTEXT->value_length=0;
      CONTEXT->tuple_num=0;
    }
value_tuple:
    /* empty */
    | COMMA LBRACE value value_list RBRACE value_tuple {
        CONTEXT->tuple_num++;
	  }
	;
value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NUMBER {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    | FLOAT {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    | SSS {
			$1 = substr($1,1,strlen($1)-2);
			CONTEXT->string_length = strlen($1);
		value_init_text(&CONTEXT->values[CONTEXT->value_length++], $1, CONTEXT->string_length);
		}
    | NULL_T {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
    ;

delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;
select:				/*  select 语句的语法解析树*/
    select_prepare select_attr FROM ID rel_list inner_join_list where order group SEMICOLON
		{
			// (CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, $4);

      Condition* this_frame_conditions = CONTEXT->conditions + CONTEXT->select_frame[CONTEXT->select_frame_index].last_condition_length;
      selects_append_conditions(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, this_frame_conditions, CONTEXT->condition_length);

			(CONTEXT->ssql + CONTEXT->select_frame_index)->flag=SCF_SELECT;//"select";
			// (CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;

      CONTEXT->condition_length = CONTEXT->select_frame[CONTEXT->select_frame_index].last_condition_length;
      CONTEXT->value_length = CONTEXT->select_frame[CONTEXT->select_frame_index].last_value_length;
      CONTEXT->select_frame_index--;
    }
    ;

select_prepare:
    SELECT {
      CONTEXT->select_frame_index++;
      CONTEXT->select_frame[CONTEXT->select_frame_index].last_condition_length = CONTEXT->condition_length;
      CONTEXT->select_frame[CONTEXT->select_frame_index].last_value_length = CONTEXT->value_length;
    }

select_attr:
    STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
    | attribute attr_list {

    }
    | aggregate attr_list {

    }
    ;
attribute:
    ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
  	| ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
    | ID DOT STAR {
      RelAttr attr;
      relation_attr_init(&attr, $1, "*");
      selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
    }
    ;
aggregate:
    agg_type LBRACE ID RBRACE {
      RelAttr attr;
			relation_attr_init(&attr, NULL, $3);
      Aggregate aggregate;
      aggregate_init(&aggregate, $1, 1, &attr, NULL);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
    | agg_type LBRACE ID DOT ID RBRACE {
      RelAttr attr;
			relation_attr_init(&attr, $3, $5);
      Aggregate aggregate;
      aggregate_init(&aggregate, $1, 1, &attr, NULL);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
    | agg_type LBRACE value RBRACE {
      Value* value = &CONTEXT->values[CONTEXT->value_length - 1];
      Aggregate aggregate;
      aggregate_init(&aggregate, $1, 0, NULL, value);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
    | agg_type LBRACE STAR RBRACE {
      value_init_string(&CONTEXT->values[CONTEXT->value_length++], "*");
      Value* value = &CONTEXT->values[CONTEXT->value_length - 1];
      Aggregate aggregate;
      aggregate_init(&aggregate, $1, 0, NULL, value);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
    ;
attr_list:
    /* empty */
    | COMMA attribute attr_list {

    }
    | COMMA aggregate attr_list {

    }
  	;
agg_type:
  	  MAX { $$ = AGG_MAX; }
    | MIN { $$ = AGG_MIN; }
    | COUNT { $$ = AGG_COUNT; }
    | AVG { $$ = AGG_AVG; }
    ;
rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, $2);
		}
    ;
inner_join_list:
    /* empty */
    | INNER JOIN ID ON condition condition_list inner_join_list{
      selects_append_relation(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, $3);
    }
    ;
where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition:
    ID comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, $2, 1, &left_attr, NULL, 0, NULL, right_value);
      CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|value comOp value 
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, $2, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|ID comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, $2, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, $2, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, $4, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			condition_init(&condition, $2, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

			Condition condition;
			condition_init(&condition, $4, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
    ;

comOp:
  	  EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IS { $$ = IS_NULL; }
    | IS NOT { $$ = IS_NOT_NULL; }
    ;
order:
    /* empty */
    | ORDER BY order_attribute order_list {
    }
    ;
order_attribute:
    ID {
      RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
    | ID DOT ID {
      RelAttr attr;
			relation_attr_init(&attr, $1, $3);
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
    | ID ASC {
      RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
    | ID DOT ID ASC {
      RelAttr attr;
			relation_attr_init(&attr, $1, $3);
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
    | ID DESC {
      RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
      Order order;
      order_init(&order, ORDER_DESC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
    | ID DOT ID DESC {
      RelAttr attr;
			relation_attr_init(&attr, $1, $3);
      Order order;
      order_init(&order, ORDER_DESC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
    ;
order_list:
    /* empty */
    | COMMA order_attribute order_list {
    }
    ;
group:
    /* empty */
    | GROUP BY group_attribute group_list {
    }
    ;
group_attribute:
    ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_group(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
  	| ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_group(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
    ;
group_list:
    /* empty */
    | COMMA group_attribute group_list {
    }
    ;
load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));
  context.select_frame_index = -1;

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
