Schoof's Algorithm                         {#mainpage}
============
Basic implementation of Schoof's algorithm

Concept Definitions
===================
We rely heavily on C++20's concepts to ensure that the templates adhere to the proper requirements. We provide basic concepts for Groups, Rings, and Fields.(Modules are a W.I.P). Each concept enfoces basic axioms that can be used by a built in. We mainly enforce existence axioms and valid operations, and assume associativity as enforcing associativty is too expensive.

Groups
------
We first define GroupElement which must have the following properties 
-   Existence and closure under addition

        {a+b}->std::same_as<GE>;

-   Existence and closure under unary operator (negation)

        {-a}->std::same_as<GE>;

-   Existence of equivalence operator

        {a==b}->std::same_as<bool>;

We next define Groups which must have the following properties
-   Existence of Element

        typename G::Element;

-   Existence of a additive identity(zero)

        {g.zero()}->std::same_as<typename G::Element>;

-   The Element must be a GroupElement

        && GroupElement<typename G::Element>;

Rings
-----
We first define RingElement which must have the following properties
-   Existence and closure under addition

        {a+b}->std::same_as<RE>;

-   Existence and closure under multiplication

        {a*b}->std::same_as<RE>;

-   Existence and closure under unary operator (negation)

        {-a}->std::same_as<RE>;

-   Existence of equivalence operator

        {a==b}->std::same_as<bool>;

We next define Rings which must have the following properties
-   Existence of Element

        typename R::Element;

-   Existence of an additive identity(zero)

        {r.zero()}->std::same_as<typename R::Element>;

-   Existence of a multiplicative identity(one)

        {r.one()}->std::same_as<typename R::Element>;

-   The Element must be a RingElement

        && RingElement<typename R::Element>;

Fields
------
We first define FieldElement which must have the following properties
-   Existence and closure under addition

        {a+b}->std::same_as<FE>;

-   Existence and closure under multiplication

        {a*b}->std::same_as<FE>;

-   Existence and closure under unary operator (negation)

        {-a}->std::same_as<FE>;

-   Existence and closure under inverse function (inverse)

        {a.inv()}->std::same_as<FE>;

-   Existence of equivalence operator

        {a==b}->std::same_as<bool>;

We next define Fields which must have the following properties
-   Existence of Element

        typename F::Element;

-   Existence of an additive identity(zero)

        {r.zero()}->std::same_as<typename F::Element>;

-   Existence of a multiplicative identity(one)

        {r.one()}->std::same_as<typename F::Element>;

-   The Element must be a FieldElement

        && FieldElement<typename F::Element>;

Modules (W.I.P)
---------------

Built Ins
=========

Using Schoof's
==============

