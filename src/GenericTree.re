type tree('a) =
  | Leaf
  | Node(tree('a), 'a, tree('a));

let rec height = t =>
  switch (t) {
  | Node(left, _, right) =>
    let leftHeight = height(left);
    let rightHeight = height(right);

    if (leftHeight > rightHeight) {
      leftHeight + 1;
    } else {
      rightHeight + 1;
    };
  | Leaf => 0
  };

let balance = t =>
  switch (t) {
  | Leaf => 0
  | Node(left, _, right) => height(right) - height(left)
  };

let rotateLeft = t =>
  switch (t) {
  | Node(
      left,
      v,
      Node(
        Node(rightLeftLeft, rightLeftValue, rightLeftRight),
        rightValue,
        Leaf,
      ),
    ) =>
    Node(
      Node(left, v, rightLeftLeft),
      rightLeftValue,
      Node(rightLeftRight, rightValue, Leaf),
    )
  | Node(left, v, Node(rightLeft, rightValue, rightRight)) =>
    Node(Node(left, v, rightLeft), rightValue, rightRight)
  | _ => t
  };

let rotateRight = t =>
  switch (t) {
  | Node(
      Node(
        Leaf,
        leftValue,
        Node(leftRightLeft, leftRightValue, leftRightRight),
      ),
      v,
      right,
    ) =>
    Node(
      Node(Leaf, leftValue, leftRightLeft),
      leftRightValue,
      Node(leftRightRight, v, right),
    )
  | Node(Node(leftLeft, leftValue, leftRight), v, right) =>
    Node(leftLeft, leftValue, Node(leftRight, v, right))
  | _ => t
  };

let rebalance = t =>
  switch (balance(t)) {
  | balanceFactor when balanceFactor > 1 =>
    /* right heavy -> rebalance */
    rotateLeft(t)
  | balanceFactor when balanceFactor < (-1) =>
    /* left heavy -> rebalance */
    rotateRight(t)
  | _ => t
  };

let rec insert = (tree, v) =>
  switch (tree) {
  | Leaf => Node(Leaf, v, Leaf)
  | Node(left, value, right) =>
    if (v < value) {
      Node(insert(left, v), value, right) |> rebalance;
    } else if (v > value) {
      Node(left, value, insert(right, v)) |> rebalance;
    } else {
      tree;
    }
  };

let rec inorder = t =>
  switch (t) {
  | Leaf => []
  | Node(left, value, right) =>
    List.concat([inorder(left), [value], inorder(right)])
  };

let fold = (z, fn, t) => inorder(t) |> List.fold_left(fn, z);

let make = numbers => numbers |> List.fold_left(insert, Leaf);
