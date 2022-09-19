#include<stdio.h>
#include<string.h>

// 后缀表达式求值
int CalculateInversePoland(char e[]){
	int ans=0;
    Element s1,s2;
	LinkStack stack;
    LinkStackInit(stack);
	for(int i=0; i<strlen(e); i++){
		//printf("%c\n",e[i]);
		if(e[i]=='+'||e[i]=='-'||e[i]=='*'||e[i]=='/'){
			// 操作符 - 出栈 - 计算 - 入栈
			if(LinkStackDe(stack,s1)==false) return 0;
			if(LinkStackDe(stack,s2)==false) return 0;
			if(e[i]=='+'){
				ans = ele_get_weight(s2)+ele_get_weight(s1);
				//printf("%lf + %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='-'){
				ans = ele_get_weight(s2)-ele_get_weight(s1);
				//printf("%lf - %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='*'){
				ans = ele_get_weight(s2)*ele_get_weight(s1);
				//printf("%lf * %lf = %lf\n",s2,s1,ans);
			}
			else{
				ans = ele_get_weight(s2)/ele_get_weight(s1);
				//printf("%lf / %lf = %lf\n",s2,s1,ans);
			}
            LinkStackEn(stack, ele_build(ans));

		}else if(e[i]=='0'||e[i]=='1'||e[i]=='2'||e[i]=='3'||e[i]=='4'||
			e[i]=='5'||e[i]=='6'||e[i]=='7'||e[i]=='8'||e[i]=='9'){
			// 数字 - 入栈
            LinkStackEn(stack, ele_build((int)e[i]-48));
		}else{
            printf("错误的字符 : %c\n",e[i]);
            return 0;
        }
	}
	return ans;
}

// 前缀表达式求值
int CalculatePoland(char e[]){
	int ans=0;
    Element s1,s2;
	int flag=0;
	LinkStack stack;
	LinkStackInit(stack);
	for(int i=strlen(e)-1; i!=-1; i--){
		if(e[i]=='+'||e[i]=='-'||e[i]=='*'||e[i]=='/'){
			// 操作符 - 出栈 - 计算 - 入栈
			if(LinkStackDe(stack,s2)==false) return 0;
			if(LinkStackDe(stack,s1)==false) return 0;
			if(e[i]=='+'){
				ans = ele_get_weight(s2)+ele_get_weight(s1);
				//printf("%lf + %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='-'){
				ans = ele_get_weight(s2)-ele_get_weight(s1);
				//printf("%lf - %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='*'){
				ans = ele_get_weight(s2)*ele_get_weight(s1);
				//printf("%lf * %lf = %lf\n",s2,s1,ans);
			}
			else{
				ans = ele_get_weight(s2)/ele_get_weight(s1);
				//printf("%lf / %lf = %lf\n",s2,s1,ans);
			}
			LinkStackEn(stack, ele_build(ans));

		}else if(e[i]=='0'||e[i]=='1'||e[i]=='2'||e[i]=='3'||e[i]=='4'||
			e[i]=='5'||e[i]=='6'||e[i]=='7'||e[i]=='8'||e[i]=='9'){
			// 数字 - 入栈
			LinkStackEn(stack, ele_build(e[i]-48));
		}
	}
	return ans;
}

int GetPriority(char c){
    switch (c) {
        case '(': return 0;
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case ')': return 3;
    }
    printf("Wrong!\n");
    return -1;
}

// 转换成后缀表达式
char* ToInversePoland(char c0[]){
	/*
	1. 遇到操作数 ->加入后缀表达式
	2. 遇到‘(’入栈, 遇到‘)’依次弹出站内运算符加入后缀表达式直到‘(’. (注意, 括号不入后缀表达式)
	3. 遇到运算符.  依次弹出运算及高于或等于当前运算符的所有运算符, 直到括号或栈空为止. 然后把当前运算符入栈. 
	4. 处理完所有字符后, 把栈中运算符依次弹出. 
	*/
    char c[64] = "(";
    strcat(c,c0);
    strcat(c,")");
    static char InversePo[64] = ""; // 后缀表达式
    int index = 0;
    LinkStack stack;
    LinkStackInit(stack);
    Element e;
    for(int i=0; i<strlen(c);i++){
        if('0'<=c[i]&&c[i]<='9'){
            InversePo[index++] = c[i];
        }else if(c[i]=='('){
            LinkStackEn(stack, ele_build((int)c[i]));
        }else if(c[i]==')'){
            while(LinkStackDe(stack,e)){
                if(ele_get_weight(e)!='(')
                    InversePo[index++] = (char)ele_get_weight(e);
                else break;
            }
        }else if(c[i]=='+'||c[i]=='-'||c[i]=='*'||c[i]=='/'){
            while(LinkStackGet(stack,e)){
                if(GetPriority((char)ele_get_weight(e))< GetPriority(c[i]))break;
                LinkStackDe(stack,e);
                if((char)ele_get_weight(e) != '(')
                    InversePo[index++] = (char)ele_get_weight(e);
            }
            LinkStackEn(stack, ele_build((int)c[i]));
        }else{
            return NULL;
        }
    }
    InversePo[index]='\0';
    return InversePo;
}

// 转换成前缀表达式
char* ToPoland(char e[]){
	return e;
}

void test_notation(){
    printf("表达式求值(续)\n");

    char s1[] = "1+(1+2)/3+(2-1)\0";
    printf("中缀转后缀 %s = %s\n",s1,ToInversePoland(s1));

	char s2[] = "112+3/+21-+\0";
	printf("后缀表达式 %s = %d\n",s2,CalculateInversePoland(s2));

	char s3[] = "++1/+123-21\0";
	printf("前缀表达式 %s = %d\n",s3,CalculatePoland(s3));
}