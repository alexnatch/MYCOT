#include "tiny_types.h"
#include "tiny_util.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

string String(char * s)
{
    return s;
}

A_stm A_CompoundStm(A_stm stm1,A_stm stm2)
{
    A_stm s = checked_malloc(sizeof(*s));
    s->kind = A_compoundStm;
    s->uni.compound.stm1 = stm1;
    s->uni.compound.stm2 = stm2;
    return s;
}

A_stm A_AssignStm(string id, A_exp exp)
{
    A_stm s = checked_malloc(sizeof(*s));
    s->kind = A_assignStm;
    s->uni.assign.id = id;
    s->uni.assign.exp = exp;
    return s;
}

A_stm A_PrintStm(A_expList exps)
{
    A_stm s = checked_malloc(sizeof(*s));
    s->kind = A_printStm;
    s->uni.print.exps = exps;
    return s;
}

A_exp A_IdExp(string id)
{
    A_exp e = checked_malloc(sizeof(*e));
    e->kind = A_idExp;
    e->uni.id = id;
    return e;
}

A_exp A_NumExp(int num)
{
    A_exp e = checked_malloc(sizeof(*e));
    e->kind = A_numExp;
    e->uni.num = num;
    return e;
}

A_exp A_OpExp(A_exp left,A_binop op, A_exp right)
{
    A_exp e = checked_malloc(sizeof(*e));
    e->kind = A_opExp;
    e->uni.oper.left = left;
    e->uni.oper.op = op;
    e->uni.oper.right = right;
    return e;
}

A_exp A_EseqExp(A_stm stm,A_exp exp)
{
    A_exp e = checked_malloc(sizeof(*e));
    e->kind = A_eseqExp;
    e->uni.eseq.stm = stm;
    e->uni.eseq.exp = exp;
    return e;
}

A_expList A_PairExpList(A_exp head,A_expList tail)
{
    A_expList el = checked_malloc(sizeof(*el));
    el->kind = A_pairExpList;
    el->uni.pair.head = head;
    el->uni.pair.tail = tail;
    return el;
}

A_expList A_LastExpList(A_exp last)
{
    A_expList el = checked_malloc(sizeof(*el));
    el->kind = A_lastExpList;
    el->uni.last = last;
    return el;
}

Table_ Table(string id,int value, Table_ tail)
{
    Table_ t = checked_malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}

Table_ t_interpStm(A_stm s, Table_ t)
{
    return NULL;
}

/*
 * Binary Tree
 */
T_tree Tree(T_tree left,string key,T_tree right)
{
    T_tree t = checked_malloc(sizeof(*t));
    t->left = left;
    t->key = key;
    t->right = right;
    return t;
}

// The Elements are always inserted on root node
T_tree tr_insert(string key, T_tree t)
{
    if( t == NULL ) return Tree(NULL,key,NULL);
    else if( strcmp(key,t->key) < 0 )
        return Tree(tr_insert(key,t->left),t->key,t->right);
    else if( strcmp(key,t->key) > 0 )
        return Tree(t->left,t->key,tr_insert(key,t->right));
    else return t;
}

T_tree tr_bindInsert(string key, void * binding ,T_tree t)
{
    if( t == NULL ) 
    {
        binding = Tree(NULL,key,NULL);
        return binding;
    }
    else if( strcmp(key,t->key) < 0 )
        return Tree(tr_bindInsert(key,binding,t->left),t->key,t->right);
    else if( strcmp(key,t->key) > 0 )
        return Tree(t->left,t->key,tr_bindInsert(key,binding,t->right));
    else return t;
}

int tr_isMemberOf(string key, T_tree t)
{
    if( t == NULL ) return TRUE;
    else if( strcmp(key,t->key) < 0 )
        return tr_isMemberOf(key,t->left);
    else if( strcmp(key,t->key) > 0 )
        return tr_isMemberOf(key,t->right);
    else return FALSE;
}

/*
 * Balanced Binary Tree
 */
B_tree BTree(B_tree lch,string key,B_tree rch,B_tree fth)
{
    B_tree t = checked_malloc(sizeof(*t));
    t->lch = lch;
    t->ldp = BT_deep(lch);
    t->key = key;
    t->rch = rch;
    t->rdp = BT_deep(rch);
    t->fth = fth;
    
    if( (t->ldp - t->rdp) > 1 ) 
    {
        // LR
        if(  (t->lch->ldp) < (t->lch->rdp) )
        {
            t->lch = BT_zag(t->lch);
            t = BT_zig(t);
        }
        // RR
        else
        {
            t = BT_zig(t);
        }
    }
    else if( (t->ldp - t->rdp) < -1 ) 
    {
        // LL
        if( (t->rch->ldp) < (t->rch->rdp) )
        {
            t = BT_zag(t);
        }
        // RL
        else
        {
            t->rch = BT_zig(t->rch);
            t = BT_zag(t);
        }
    }
    //BT_print(t);
    
    return t;
}

// rotate towards left
B_tree BT_zag(B_tree t)
{
    if( (!t) && (!t->rch) ){return;}
    B_tree temp;
    temp = t->rch;
    temp->fth = t->fth;
    t->rch = t->rch->lch;
    if(t->rch) t->rch->fth = t;
    t->fth = temp;
    t->rdp = BT_deep(t->rch);
    temp->lch = t;
    temp->ldp = BT_deep(t);
    // Now temp is the root node
    return temp;
}

// rotate towards right
B_tree BT_zig(B_tree t)
{
    if( (!t) && (!t->lch) ){return;}
    B_tree temp;
    temp = t->lch;
    temp->fth = t->fth;
    t->lch = t->lch->rch;
    if(t->lch) t->lch->fth = t;
    t->fth = temp;
    t->ldp = BT_deep(t->lch);
    temp->rch = t;
    temp->rdp = BT_deep(t);
    // Now temp is the root node
    return temp;
}

int BT_deep(B_tree t)
{
    if( t == NULL) return 0;
    else if ( (t->ldp) > (t->rdp) ) return t->ldp + 1;
    else return t->rdp + 1;
}

B_tree BT_insert(string key, B_tree t)
{
    if( t == NULL ) 
    {
        return BTree(NULL,key,NULL,NULL);
    }
    else
    {
        if( strcmp(key,t->key) < 0 )
        {
            B_tree temp = BTree(BT_insert(key,t->lch),t->key,t->rch,t->fth);
            temp->lch->fth = temp;
            return temp;
        }
        else if( strcmp(key,t->key) > 0 )
        {
            B_tree temp = BTree(t->lch,t->key,BT_insert(key,t->rch),t->fth);
            temp->rch->fth = temp;
            return temp;
        }
        else return t;
        /*
        return t;
        */
    }
}

void print_blank(int count)
{
    while(count--)
    {
        printf("    ");
    }
}


void BT_print(B_tree t)
{
    if( t == NULL )
    { return ; }
    else 
    {
        print_blank(t->ldp);printf("%s",t->key);print_blank(t->rdp);printf("\n");
        BT_print(t->lch);
        BT_print(t->rch);
    }
}

/*
 * AVL Tree
 */

/*
 * Splay Tree
 */
