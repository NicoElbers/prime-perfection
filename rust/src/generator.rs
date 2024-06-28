use crate::prime_checker::is_prime;

pub fn gen_primes(max: u64) -> Vec<u64> {
    let mut result: Vec<u64> = Vec::new();

    for n in 2..=max {
        if is_prime(n) {
            result.push(n);
        }
    }

    result
}
