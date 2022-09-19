//算符优先法
#include<stdio.h>
#include<string>

char priority[7][7]={
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},   // 此行"("=")"表示左右括号相遇，括号内运算已完成
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}    // "=" 表示整个表达式求值完毕
};                               //  "0"表示不可能出现这种情况 ( 语法错误 )

//Precede 用于判断运算符栈栈顶运算符 a1 与读入运算符 a2 之间的优先关系函数
char Procede(char a,char b){   // 建立 pre[][] 到 运算符间的映射关系
    int i,j;
    switch(a){
        case'+':i=0;break;
        case'-':i=1;break;
        case'*':i=2;break;
        case'/':i=3;break;
        case'(':i=4;break;
        case')':i=5;break;
        case'#':i=6;break;   // # 是表达式的结束符
    }
    switch(b){
        case'+':j=0;break;
        case'-':j=1;break;
        case'*':j=2;break;
        case'/':j=3;break;
        case'(':j=4;break;
        case')':j=5;break;
        case'#':j=6;break;
    }
    return priority[i][j];
}

int Operate(int m,int n,char x){
    if(x=='+')
        return m+n;
    else if(x=='-')
        return n-m;
    else if(x=='*')
        return m*n;
    else
        return n/m;
}

int ExpressionEvaluation(char s[]){
    strcat(s, "#");// 运算式尾部加 "#"--结束运算符
    LinkStack OPND;
    LinkStack OPTR;
    LinkStackInit(OPND); // Operand stack
    LinkStackInit(OPTR); // Operator stack
    LinkStackEn(OPTR, ele_build((int)'#'));

    char c=s[0];
    int k=1;
    Element e;

    while(1){
        //表达式未读完或者运算未完
        LinkStackGet(OPTR,e);
        //printf("[%c,%d]",c, ele_get_weight(e));
        if(c=='#' && ele_get_weight(e)==(int)'#') break;
        // 运算
        int y=0;
        if((int)c>=(int)'0' && (int)c<=(int)'9'){
            while(c>='0'&&c<='9'){  // 读入连续的数字
                y=y*10+(c-'0');
                c=s[k++];
            }
            LinkStackEn(OPND, ele_build(y));// 把读进的数字入数字栈
        }
        else {
            LinkStackGet(OPTR, e);
            switch (Procede(ele_get_weight(e), c)) {
                case '<':  //栈顶元素优先权低
                    LinkStackEn(OPTR, ele_build((int) c));
                    c = s[k++];
                    break;
                case '=':
                    LinkStackDe(OPTR, e);
                    c = s[k++];  // 读入下一个字符
                    break;
                case '>':  //退栈并将运算结果入栈
                    LinkStackGet(OPTR, e);
                    char x = (char) ele_get_weight(e);
                    LinkStackDe(OPTR, e);
                    LinkStackGet(OPND, e);
                    int m = ele_get_weight(e);
                    LinkStackDe(OPND, e);
                    LinkStackGet(OPND, e);
                    int n = ele_get_weight(e);
                    LinkStackDe(OPND, e);
                    LinkStackEn(OPND, ele_build(Operate(m, n, x)));
                    break;
            }
        }
    }
    LinkStackDe(OPND, e);
    LinkStackDestroy(OPND);
    LinkStackDestroy(OPTR);
    return ele_get_weight(e);
}


void test_expression_evaluation(){
    printf("中缀表达式求值\n");
    char str1[64] = "1+3*(8-2)";
    printf("1+3*(8-2) = %d\n",ExpressionEvaluation(str1));
    char str2[64] = "1+2";
    printf("1+2 = %d\n",ExpressionEvaluation(str2));
    char str3[64] = "1+3*8";
    printf("1+3*8 = %d\n",ExpressionEvaluation(str3));
    char str4[64] = "3+(15/(7-(1+1)))-(2+(1+1))";
    printf("3+15/(7-(1+1))-(2+(1+1)) = %d\n",ExpressionEvaluation(str4));
    char str5[64] = "8-7-6-5-5";
    printf("8-7-6-5-5 = %d\n",ExpressionEvaluation(str5));
}