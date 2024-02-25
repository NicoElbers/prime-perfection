use std::time::Instant;

fn main() {
    let now = Instant::now();
    let res = gen_primes(1_000_000_000);
    let elapsed = now.elapsed().as_millis();

    println!("Result had {} results", res.len());
    println!("This took {elapsed}ms");
}

fn gen_primes(max: u64) -> Vec<u64> {
    let mut result: Vec<u64> = Vec::new();

    for n in 2..=max {
        if is_prime(n) {
            result.push(n);
        }
    }

    result
}

fn is_prime(n: u64) -> bool {
    debug_assert!(n >= 2);

    if n < 4 {
        return true;
    }

    if n % 2 == 0 || n % 3 == 0 {
        return false;
    }

    let mut i = 5u64;
    while i * i <= n {
        if n % i == 0 {
            return false;
        }
        if n % (i + 2) == 0 {
            return false;
        }
        i += 6;
    }

    true
}
