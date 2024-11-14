# tsp

## Traveling Salesman Problem

Write a Program that will read a set of city coordinates under the form `%f, %f` from the `stdin` and will print the length of the shortest possible path containting all these ities under the form `%.2f`.

---

### Example

input:

- `stdin` with filename such as, `somewhat.txt`
- no more than 11 city coordinates in a file.

```
1, 1
0, 1
1, 0
0, 0
```

output:

- `stdout` with format, `"%.2f"`

expected execution:

```sh
$ ./tsp < somewhat.txt
```