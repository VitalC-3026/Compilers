
;; Function main (main, funcdef_no=23, decl_uid=2444, cgraph_uid=23, symbol_order=23)

main ()
{
  int f;
  int n;
  int i;
  int D.2453;

  scanf ("%d", &n);
  i = 2;
  f = 1;
  goto <D.2450>;
  <D.2449>:
  f = f * i;
  i = i + 1;
  <D.2450>:
  n.0_1 = n;
  if (i <= n.0_1) goto <D.2449>; else goto <D.2451>;
  <D.2451>:
  printf ("%d\n", f);
  n = {CLOBBER};
  D.2453 = 0;
  goto <D.2454>;
  <D.2454>:
  return D.2453;
}



;; Function printf (<unset-asm-name>, funcdef_no=15, decl_uid=798, cgraph_uid=15, symbol_order=15)

__attribute__((__artificial__, __gnu_inline__, __always_inline__))
printf (const char * restrict __fmt)
{
  int D.2455;

  D.2455 = __printf_chk (1, __fmt, __builtin_va_arg_pack ());
  goto <D.2456>;
  <D.2456>:
  return D.2455;
}


