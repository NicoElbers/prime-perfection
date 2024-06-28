pub fn is_prime(n: u64) -> bool {
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
