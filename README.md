SEXPR REPL
==========

A repl(read-eval-print loop) in the domain of sexprs. An sexpr is one of the following:

* integer
* floating point
* atom
* string

Current features
----------------

-tokenizer -- retrieves one token at a time from an input buffer. a token is one of the following:

* integer
* floating point
* atom
* string
* left or right parenthesis
* left or right bracket
* dot

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

*logical*
* and ('and')
* or ('or')
* not ('not')
