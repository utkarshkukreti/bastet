open Interface;

let approximately_equal: (~tolerance:float, float, float) => bool =
  (~tolerance, a, b) => Js.Math.abs_float(a -. b) <= tolerance;

module Additive = {
  module Magma: MAGMA with type t = float = {
    type t = float;
    let append = (+.);
  };
  module Semigroup: SEMIGROUP with type t = float = {
    include Magma;
  };
  module Monoid: MONOID with type t = float = {
    include Semigroup;
    let empty = 0.0;
  };
};

module Multiplicative = {
  module Magma: MAGMA with type t = float = {
    type t = float;
    let append = (*.);
  };
  module Semigroup: SEMIGROUP with type t = float = {
    include Magma;
  };
  module Monoid: MONOID with type t = float = {
    include Semigroup;
    let empty = 1.0;
  };
};

module Eq: EQ with type t = float = {
  type t = float;
  let eq = (==);
};

module Ord: ORD with type t = float = {
  include Eq;
  let compare = unsafe_compare;
};

module Bounded: BOUNDED with type t = float = {
  include Ord;
  let top = 2147483647.0;
  let bottom = -2147483648.0;
};

module Show: SHOW with type t = float = {
  type t = float;
  let show = string_of_float;
};

module Semiring: SEMIRING with type t = float = {
  type t = float;
  let add = (+.);
  let zero = 0.0;
  let multiply = (*.);
  let one = 1.0;
};

module Ring: RING with type t = float = {
  include Semiring;
  let subtract = (-.);
};

module Commutative_Ring: COMMUTATIVE_RING with type t = float = {
  include Ring;
};

module Division_Ring: DIVISION_RING with type t = float = {
  include Ring;
  let reciprocal = (a) => 1.0 /. a;
};

module Euclidean_Ring: EUCLIDEAN_RING with type t = float = {
  include Commutative_Ring;
  let degree = (_) => 1;
  let divide = (/.);
  let modulo = (_, _) => 0.0;
};

module Field: FIELD with type t = float = {
  include Euclidean_Ring;
  include (Division_Ring: DIVISION_RING with type t := t);
};

module Infix = {
  module Additive = {
    include Infix.Semigroup(Additive.Semigroup);
  };
  module Multiplicative = {
    include Infix.Semigroup(Multiplicative.Semigroup);
  };
  include Infix.Eq(Eq);
  include Infix.Ord(Ord);
  include Infix.Euclidean_Ring(Euclidean_Ring);
};