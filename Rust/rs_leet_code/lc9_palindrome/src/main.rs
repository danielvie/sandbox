// decription 
// determine whether an integer is a palindrome. an integer is a palindrom when it
// reads tha same backward as forward
//
// example 1:
// Input: 121
// Output: true

pub struct Solution;

impl Solution {
    pub fn palindrome(number:i32) -> bool {
        
        let txt = number.to_string();
        return txt == txt.chars().rev().collect::<String>();
    }

    pub fn palindrome_nostring(x:i32) -> bool {
        
        if x < 0 {
            return false;
        }
        
        let mut rev:i32 = 0;
        let mut num:i32 = x;
        
        while num > 0 {
            rev = rev*10 + num % 10;
            num /= 10;
        }
        
        x == rev
    }
}

fn main() {
    
    println!("adsfasdfas");
    // unit tests
    assert!(Solution::palindrome(129));
    assert!(Solution::palindrome(121));
    assert!(Solution::palindrome(-121));

    assert!(!Solution::palindrome_nostring(129));
    assert!(Solution::palindrome_nostring(121));
    assert!(Solution::palindrome_nostring(-121));
}
