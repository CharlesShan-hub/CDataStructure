#include <string.h>

typedef LinkStack Stack;

bool BracketCheck(char str[]){
    Stack S;
    LinkStackInit(S);
    char x;
    Element e;
    for(int i=0;i<strlen(str);i++){
        printf("%c",str[i]);
        if(str[i]=='('||str[i]=='['||str[i]=='{')
            LinkStackEn(S, ele_build(int(str[i])));
        if(str[i]==')'||str[i]==']'||str[i]=='}') {
            if (LinkStackEmpty(S))
                return false;
            LinkStackDe(S, e);
            x = (char) ele_get_weight(e);
            if (x == ')' && str[i] != '(') return false;
            if (x == ']' && str[i] != '[') return false;
            if (x == '}' && str[i] != '{') return false;
        }
    }
    return LinkStackEmpty(S);
}

void test_bracket_check(){
    printf("括号匹配算法\n");
    char str1[] = "[123]({12})";
    printf(": %d\n",BracketCheck(str1));
    char str2[] = "[]][[12({12})]";
    printf(": %d\n",BracketCheck(str2));
}
