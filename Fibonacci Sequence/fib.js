
fib(0, 1, 25);

function fib(a, b, n){
  if(n != 0){
    console.log(a);
    fib(b, a+b, n-1);
  }else return n;
}