
;; Function max (max, funcdef_no=0, decl_uid=2251, cgraph_uid=0, symbol_order=2)

max (int a, int b)
{
  int D.2258;

  if (a >= b) goto <D.2256>; else goto <D.2257>;
  <D.2256>:
  D.2258 = a;
  goto <D.2259>;
  <D.2257>:
  D.2258 = b;
  goto <D.2259>;
  <D.2259>:
  return D.2258;
}



;; Function main (main, funcdef_no=1, decl_uid=2253, cgraph_uid=1, symbol_order=3)

main ()
{
  int D.2260;

  scanf ("%d, %d", &a, &b);
  b.0_1 = b;
  a.1_2 = a;
  _3 = max (a.1_2, b.0_1);
  printf ("max is: %d\n", _3);
  D.2260 = 0;
  goto <D.2261>;
  D.2260 = 0;
  goto <D.2261>;
  <D.2261>:
  return D.2260;
}


