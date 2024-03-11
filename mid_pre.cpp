//本程序只能处理有关运算符+、-、*、/的中缀表达式，不能是÷或者×及其他运算
//界限符只能是英文状态的左右括号即'('、')'，操作数只能是整数
//本程序不会检查输入的中缀表达式是否正确，因此请您核验好自己的式子是否正确
#include<stdio.h>
#include<string.h> //strlen的头文件，用于判断字符串长度
#include<stdlib.h> //malloc、free的头文件
#define size 50//假定要转换的中缀表达式的字符数在50个以内
typedef struct Linknode{ //定义链栈及结点
    char data; //数据域
    struct Linknode *next; //指针域
}*LiStack;
bool InitStack(LiStack &S){ //链栈的初始化，不带头结点
    S=NULL; //刚开始没有结点
    return true;
}
bool StackEmpty(LiStack S){ //判断栈空
    return S==NULL;
}
bool Push(LiStack &S,char x){ //将元素x入栈
    Linknode *s=(Linknode *)malloc(sizeof(Linknode)); //创建新结点
    if(s==NULL) //内存不足，创建失败
        return false;
    s->data=x;
    s->next=S; //将结点s作为链栈的栈顶结点
    S=s; //栈顶指针S指向结点s
    return true;
}
bool Pop(LiStack &S,char &x){ //栈顶元素出栈，将值赋给x
    if(S==NULL)
        return false; //栈空则返回NULL
    x=S->data;
    Linknode *p=S;
    S=S->next;
    free(p);
    return true;
}
int main(){
    char temp,a[size],b[size]; //静态数组a、b分别存放要转换的中缀表达式和转换后的前缀表达式,字符变量temp存放弹出的栈顶元素
    scanf("%s",&a); //需要您输入中缀表达式
    LiStack S;//初始化一个栈，用于保存括号和暂时还不能确定运算顺序的运算符
    InitStack(S); //初始化链栈
    int i,j,length=strlen(a); //length为输入的中缀表达式的总长度，i、j分别为静态数组a、b的索引下标
    for(i=length-1,j=0;i>=0;i--){ //从右到左扫描中缀表达式的各个字符，直到末尾
        if(a[i]>=48 && a[i]<=57){ //若当前字符是数字,字符0-9的ACSII码范围是[48,57]
            b[j++]=a[i];
            if(a[i-1]=='+'||a[i-1]=='-'||a[i-1]=='*'||a[i-1]=='/') //若上一个字符是运算符，即+、-、*、/，则b加一个空格，以免不同的操作数混在一起
                b[j++]=' ';
        }
        else if(a[i]==')')
            Push(S,a[i]); //若当前字符是右括号则直接入栈
        else if(a[i]=='('){ //若当前字符是左括号
            while(StackEmpty(S)==0){ //栈非空则不断弹出栈内字符并加入前缀表达式
                Pop(S,temp);
                if(temp==')') //直到弹出右括号停止，注意这个)不加入前缀表达式
                    break;
                b[j++]=temp;
                b[j++]=' '; //加一个空格，从而将字符隔开
            }
        }
        else switch(a[i]){ //若当前字符是运算符
                case '*': case '/':{
                    while(StackEmpty(S)==0){ //若栈非空，则弹出栈中优先级低于或等于当前运算符的所有运算符，并将这些运算符加入前缀表达式
                        Pop(S,temp);
                        if(temp=='+'||temp=='-'||temp=='/'||temp=='*'){
                            b[j++]=temp;
                            b[j++]=' '; //加一个空格，从而将字符隔开
                        }
                        else if(temp==')'){ //若栈顶元素是右括号或者是优先级高于当前字符的运算符，则将栈顶元素入栈
                            Push(S,temp);
                            break;
                        }
                    }
                    Push(S,a[i]); //把当前字符入栈
                    break;
                }
                case '-': case '+':{
                    while(StackEmpty(S)==0){ //若栈非空，则弹出栈中优先级低于或等于当前运算符的所有运算符，并将这些运算符加入前缀表达式
                        Pop(S,temp);
                        if(temp==')'||temp=='*'||temp=='/'){ //若栈顶元素是右括号或者是优先级高于当前字符的运算符，则将栈顶元素入栈
                            Push(S,temp);
                            break;
                        }
                        else if(temp=='+'||temp=='-'){
                            b[j++]=temp;
                            b[j++]=' '; //加一个空格，从而将字符隔开
                        }
                    }
                    Push(S,a[i]); //把当前字符入栈
                    break;
                }
            }
    }
    while(StackEmpty(S)==0){ //栈非空时依次弹出栈顶元素并加入前缀表达式
        Pop(S,temp);
        b[j++]=temp;
        b[j++]=' '; //加一个空格，从而将字符隔开
    }
    printf("结果是：\n");
    for(i=j-1;i>=0;i--) //b中存放字符的索引区间为[0,j-1]
        printf("%c",b[i]); //倒序输出b中的元素
    printf("\n");
    return 0;
}

