open Jest;
open Expect;
open Tree;

let _ =
  describe("Tree", () =>
    test("sum", () => {
      let t = make([1, 2, 3]);

      expect(sum(t)) |> toBe(6);
    })
  );
