open Jest;
open Expect;
open GenericTree;

describe("Tree", () => {
  describe("folding", () => {
    test("string concat (ordered)", () => {
      let t = make(["1", "2", "3"]);

      expect(fold("", (++), t)) |> toBe("123");
    });

    test("string concat (reversed)", () => {
      let t = make(["3", "2", "1"]);

      expect(fold("", (++), t)) |> toBe("123");
    });

    test("char concat (ordered)", () => {
      let t = make(['1', '2', '3']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t)) |> toBe("123");
    });

    test("char concat (reversed)", () => {
      let t = make(['3', '2', '1']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t)) |> toBe("123");
    });
  });

  describe("rotations", () => {
    test("left-right (312)", () => {
      let t = make(['3', '1', '2']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t)) |> toBe("123");
    });

    test("right-left (132)", () => {
      let t = make(['1', '3', '2']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t)) |> toBe("123");
    });

    test("left", () => {
      let t = make(['M', 'N', 'O']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t)) |> toBe("MNO");
    });

    test("right", () => {
      let t = make(['M', 'N', 'O', 'L', 'K']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t))
      |> toBe("KLMNO");
    });

    test("right-left", () => {
      let t = make(['M', 'N', 'O', 'L', 'K', 'Q', 'P']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t))
      |> toBe("KLMNOPQ");
    });

    test("left-right", () => {
      let t = make(['M', 'N', 'O', 'L', 'K', 'Q', 'P', 'H', 'I']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t))
      |> toBe("HIKLMNOPQ");
    });

    test("parent", () => {
      let t = make(['M', 'N', 'O', 'L', 'K', 'Q', 'P', 'H', 'I', 'A']);

      expect(fold("", (s, c) => s ++ String.make(1, c), t))
      |> toBe("AHIKLMNOPQ");
    });
  });

  describe("balance", () => {
    test("left-right (312)", () => {
      let t = make(['3', '1', '2']);

      expect(balance(t)) |> toBe(0);
    });

    test("right-left (132)", () => {
      let t = make(['1', '3', '2']);

      expect(balance(t)) |> toBe(0);
    });

    test("left", () => {
      let t = make(['M', 'N', 'O']);

      expect(balance(t)) |> toBe(0);
    });

    test("right", () => {
      let t = make(['M', 'N', 'O', 'L', 'K']);

      expect(balance(t)) |> toBe(-1);
    });

    test("right-left", () => {
      let t = make(['M', 'N', 'O', 'L', 'K', 'Q', 'P']);

      expect(balance(t)) |> toBe(0);
    });

    test("left-right", () => {
      let t = make(['M', 'N', 'O', 'L', 'K', 'Q', 'P', 'H', 'I']);

      expect(balance(t)) |> toBe(-1);
    });

    test("parent", () => {
      let t = make(['M', 'N', 'O', 'L', 'K', 'Q', 'P', 'H', 'I', 'A']);

      expect(balance(t)) |> toBe(-1);
    });
  });
});
