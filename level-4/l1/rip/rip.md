Given a string containing only parentheses '(' and ')', write a program that removes the minimum number of parentheses to make the string valid (balanced). Print all possible valid combinations that can be formed.

Requirements:

- A valid string has an equal number of opening and closing parentheses
- Every closing parenthesis must have a corresponding opening parenthesis that comes before it
- Leading closing parentheses and trailing opening parentheses should be removed as they can never be part of a valid sequence
- If multiple solutions exist, print all of them

Example input/output:

```
Input: "(()"
Possible outputs: "()"

Input: ")("
Possible outputs: ""

Input: "((())"
Possible outputs: "(())"
```

This is similar to a classic parentheses validation problem but with the additional requirement of finding all possible valid combinations that can be formed by removing characters, not just one solution.

---
