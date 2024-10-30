mod generator;
mod prime_checker;

use std::{env::args, time::Instant};

use crate::generator::gen_primes;

fn main() {
    // let max: u64 = args()
    //     .nth(1) //
    //     .map_or(1, |val| val.parse().unwrap_or(1));
    //
    // let loops: u64 = args()
    //     .nth(2) //
    //     .map_or(1, |val| val.parse().unwrap_or(1));

    // println!("Calculating all primes under {max}");
    // println!("For {loops} loops");

    let max = 1_000_000;
    let loops = 1;

    let now = Instant::now();
    for i in 0..loops {
        let res = gen_primes(max);
        #[cfg(debug_assertions)]
        println!("Result had {} results in loop {i}", res.len());
    }
    let elapsed = now.elapsed().as_millis();

    println!("This took {elapsed}ms");
}
