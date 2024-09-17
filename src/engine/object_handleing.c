#include "dataTypes.h"
#include "object_handleing.h"
#include "engine_internal.h"
#include "rendeing.h"
#include "errors.h"

Objnode *root()
{
        return retrive_ptr(0); // the frame a 0 is allways the root it is allocated in engineMain
}

Objnode *next_node(Objnode *n)
{
        return n->right;
}

Objnode *sub_node(Objnode *n)
{
        return n->left;
}

Objnode *new_objnode()
{
        return allocate(sizeof(Objnode));
}

Objnode *prev_node(Objnode *root_node, Objnode *n)
{
        Objnode *w = root_node;
        if (n == w) {
                return n;
        }
        while (true) {
                if (w == (void *)0) {
                        FATAL_ERROR("prev_node cant be found (have you provided the right root?)", illegal_operation);
                }
                if (next_node(w) == n) {
                        return w;
                }
                w = next_node(w); 
        }
}

void recer_free(Objnode *n)
{
        if (n->right != (void *)0){
                recer_free(n->right);
        }
        if (n->left != (void *)0){
                recer_free(n->left);
        }
        free_object(n->obj);
        deallocate(n);
}

void free_objnode(Objnode *n)
{
        if (n == root()) {
                FATAL_ERROR("You cant free the root Objnode", illegal_operation);
        }
        if (next_node(n) != (void *)0) {
                Objnode *p_node = prev_node(root(), n);
                p_node->right = next_node(n);
        }
        if (sub_node(n) != (void *)0)
        {
                recer_free(sub_node(n));
        }
        free_object(n->obj);
        deallocate(n);

}

void add_node(Objnode *root, Objnode *new_node)
{
        Objnode *w = root;
        Objnode *nn = (void *)0;
        while (true) {
                nn = next_node(w);
                if (nn == (void *)0) {
                        break;
                }
                w = nn;
        }
        w->right = new_node;
}

void add_sub_node(Objnode *node, Objnode *new_node)
{
        if (node == root()) {
                FATAL_ERROR("the root obj cant have sub_objects", illegal_operation);
        }
        Objnode *sub_root = sub_node(node);
        add_node(sub_root, new_node);
}

Objnode *tail_node(Objnode *root_node)
{
        Objnode *w = root_node;
        while (true) {
                if (next_node(w) == (void *)0) {
                        return w;
                }
                w = next_node(w);
        }
}

void add_object(Object *obj)
{
        Objnode *t_node = tail_node(root());
        Objnode *n_objnode = new_objnode();
        n_objnode->obj = obj;
        t_node->right = n_objnode;
        
}

void add_man(char *path)
{
        Object *new_obj = parce_manafest(path);
        add_object(new_obj);
}
