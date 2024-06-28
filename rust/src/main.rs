mod generator;
mod prime_checker;

use std::{env::args, time::Instant};

use crate::generator::gen_primes;

fn main() {
    let mut args = args();

    let max: u64 = args
        .nth(1) //
        .map(|val| val.parse().unwrap_or(1))
        .unwrap_or(1);

    let loops: u64 = match args.nth(2) {
        Some(arg) => arg.parse().unwrap_or(1),
        None => 1,
    };

    println!("Calculating all primes under {max}");

    let now = Instant::now();
    for i in 0..loops {
        let res = gen_primes(max);
        #[cfg(debug_assertions)]
        println!("Result had {} results in loop {i}", res.len());
    }
    let elapsed = now.elapsed().as_millis();

    println!("This took {elapsed}ms");
}
