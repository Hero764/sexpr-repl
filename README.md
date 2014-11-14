SCHEME INTERPRETER
==================

An interpreter for a (as of right now) subset of the Scheme dialect of Lisp. 


Current features
----------------

The following sexprs are supported:

* integer
* floating point
* atom
* string
* boolean

* *define* names as sexprs
* *define* names as procedures
* pass arguments to the procedures

Builtin Operators
-----------------

*arithmetic*
* addition ('+')
* subtraction ('-')
* multiplication ('\*')
* division ('/')
* modulo ('%')
* negative ('-')

*comparison*
* greater than ('>')
* greater than or equal to ('>=')
* less than ('<')
* less than or equal to ('<=')
* equal to ('=')
* not equal to ('!=')
