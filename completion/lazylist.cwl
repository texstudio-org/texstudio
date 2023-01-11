# lazylist package
# Matthew Bertucci 2023/01/08 for v1.0a

# Functions
\Identity{arg}
\Error
\First{arg1}{arg2}
\Second{arg1}{arg2}
\Compose{func1}{func2}{arg}
\Twiddle{func}{arg1}{arg2}

# Booleans
\True{true}{false}
\False{true}{false}
\Not{func}{true}{false}
\And{arg1}{arg2}
\Or{arg1}{arg2}
\Lift{predicate}{func1}{func2}{arg}
\Lessthan{num1}{num2}{true}{false}
\gobblefalse#*
\gobbletrue#*
\TeXif{if-statement}{true}{false}

# Lists
\Nil
\Cons{head}{tail}
\Stream{item}
\Singleton{item}
\Head{list}
\Tail{list}
\Foldl{func}{arg}{list}
\Foldr{func}{arg}{list}
\Cat{list1}{list2}
\Reverse{list}
\All{predicate}{list}
\Some{predicate}{list}
\Isempty{list}
\Filter{predicate}{list}
\Map{func}{list}
\Insert{order}{item}{list}
\Insertsort{order}{list}

# Sorting reference lists
\Unlistize{list}
\Commaize{arg1}{arg2}#*
\Listize[a,b,c,...]
\Show