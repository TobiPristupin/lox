#script that automatically generates c++ expression classes.
#to generate an expression class add it to the classes list in the format: classname : Type1 field1, Type2 field2
classes = [
    "BinaryExpr : Expression* left, Expression* right, Token* op",
    "GroupingExpr : Expression* expr",
    "UnaryExpr : Token* op, Expression*  right",
    "LiteralExpr : lox_literal_t* literal"
]
# "Grouping : Expr expression",
# "Literal  : Object value",
# "Unary    : Token operator, Expr right"

for _class in classes:
    _class = _class.split(":")
    classname = _class[0]
    fields = [field.split() for field in _class[1].split(",")]

    print(f"struct {classname}: public Expression {{")
    for type, name in fields:
        print(f"    {type} {name};")

    print()
    constructor = "\t" + classname + "("
    for i, field in enumerate(fields):
        type, name = field
        constructor += type + " " + name
        if i != len(fields) - 1: constructor += ", "
    constructor += ") : "
    for i, field in enumerate(fields):
        type, name = field
        constructor += f"{name}({name})"
        if i != len(fields) - 1: constructor += ", "
    constructor += " {}"

    print(constructor)

    print("};")
    print()



