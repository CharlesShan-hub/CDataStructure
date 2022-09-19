/**
 * Element
 * 元素
 * 
 * 表示链表、栈与队列、树与图的结点元素
 * 
 * 用法举例:
 * Element e;
 * ele_set_weight(e,1);
 * printf("%d\n",ele_get_weight(e)); // print: 1
 * 
 */

typedef long int ElementWeight;
typedef struct Element
{
	// Weight is the value of an Element
    ElementWeight weight;
	// Others to be defind here
	// ...
}Element;


ElementWeight ele_get_weight(Element e){
	return e.weight;
}

void ele_set_weight(Element &e,ElementWeight weight){
	e.weight = weight;
}

Element ele_build(ElementWeight weight){
	Element e;
	ele_set_weight(e,weight);
	return e;
}

void ele_init(Element &e,ElementWeight weight){
    ele_set_weight(e,weight);
}

void ele_copy(Element &to, Element from){
	ele_set_weight(to,from.weight);
}

bool ele_equal(Element e1, Element e2){
	return e1.weight == e2.weight;
}

void ele_print(Element e){
    printf("%ld ",ele_get_weight(e));
}
