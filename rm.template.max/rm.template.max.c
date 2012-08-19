/**
	@file
	rm.template.max - a template Max object
        based on simplemax by jeremy bernstein - jeremy@bootsquad.com	
	
    Copyright (c) 2012 Roth Michaels
*/

#ifndef MAX_SDK_INCLUDES
#define MAX_SDK_INCLUDES
#include "ext.h"
#include "ext_obex.h"
#endif

/* Max object struct */
typedef struct _rm_template_max  {
	t_object    ob;			// the object itself (must be first)
} t_rm_template_max;

/* Max method function prototypes */
void *rm_template_max_new(t_symbol *s, long argc, t_atom *argv);
void rm_template_max_free(t_rm_template_max *x);
void rm_template_max_assist(t_rm_template_max *x, void *b, long m, long a, char *s);

/* class pointer */
t_class *rm_template_max_class;


/* load the external */
int main(void)
{	
    // create class
	t_class *c;
	c = class_new("rm.template.max", 
                  (method)rm_template_max_new, 
                  (method)rm_template_max_free, 
                  (long)sizeof(t_rm_template_max), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
    // declare assist
    class_addmethod(c, (method)rm_template_max_assist, "assist", A_CANT, 0);  
	
    // register class
	class_register(CLASS_BOX, c);
	rm_template_max_class = c;
    
	post("I am the rm.template.max object");
    
	return 0;
}

/* instantiate object */
void *rm_template_max_new(t_symbol *s, long argc, t_atom *argv)
{
	t_rm_template_max *x = NULL;
    long i;
	
	// object instantiation
	if ((x = (t_rm_template_max *)object_alloc(rm_template_max_class))) {
        object_post((t_object *)x, "a new %s object was instantiated: 0x%X", s->s_name, x);
        object_post((t_object *)x, "it has %ld arguments", argc);
        
        for (i = 0; i < argc; i++) {
            if ((argv + i)->a_type == A_LONG) {
                object_post((t_object *)x, "arg %ld: long (%ld)", i, atom_getlong(argv+i));
            } else if ((argv + i)->a_type == A_FLOAT) {
                object_post((t_object *)x, "arg %ld: float (%f)", i, atom_getfloat(argv+i));
            } else if ((argv + i)->a_type == A_SYM) {
                object_post((t_object *)x, "arg %ld: symbol (%s)", i, atom_getsym(argv+i)->s_name);
            } else {
                object_error((t_object *)x, "forbidden argument");
            }
        }
	}
    
	return (x);
}

#pragma mark Max Methods

/* show inlet/outlet assist messages on mouseover in Max */
void rm_template_max_assist(t_rm_template_max *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		sprintf(s, "I am inlet %ld", a);
	} 
	else {	// outlet
		sprintf(s, "I am outlet %ld", a); 			
	}
}

#pragma mark -

/* do any cleanup before freeing */
void rm_template_max_free(t_rm_template_max *x)
{
	;
}

