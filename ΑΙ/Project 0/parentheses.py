# Τhe top item of the Stack is the last item of the list used

class Stack:

    def __init__(self):
        self.list = []

    def push(self, item):
        self.list.append(item)

    def pop(self):
        return self.list.pop()
    
    def empty(self):
        return (len(self.list) == 0)

def main():

    string = str(input())

    check = Stack()

# Push open parentheses until we get a close one
# If the close one is the same with the open then pop the open and continue
# If not then the string is not balanced

    for s in string:
        if s == '(' or s =='[' or s == '{':
            check.push(s)
        else:
            if s == ')' and check.pop() != '(':
                return False
            if s == ']' and check.pop() != '[':
                return False
            if s == '}' and check.pop() != '{':
                return False

# We need to check the possibility of a string with only open parentheses(ex. [[[)
    if not check.empty():
        return False

    return True

if __name__ == "__main__":
    main()

