open Jest;
open Expect;
open IntTree;

describe("Tree", () =>
  test("sum", () => {
    let t = make([1, 2, 3]);

    expect(sum(t)) |> toBe(6);
  })
);
