open Jest;
open Expect;
open GenericTree;

describe("Tree", () => {
  test("string concat", () => {
    let t = make(["1", "2", "3"]);

    expect(fold("", (++), t)) |> toBe("123");
  });

  test("char concat", () => {
    let t = make(['1', '2', '3']);

    expect(fold("", (s, c) => s ++ String.make(1, c), t)) |> toBe("123");
  });
});
