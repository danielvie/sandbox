use std::{collections::HashMap};

pub struct Solution;

// impl Solution {
//     pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
//         let mut hash: HashMap<i32, usize> = HashMap::new();
//         for (i, num) in nums.iter().enumerate() {
//             let complement = target - num;
//             if let Some(&complement_index) = hash.get(&complement) {
//                 return vec![complement_index as i32, i as i32];
//             }
//             hash.insert(*num, i);
//         }

//         vec![]
//     }
// }

// bruteforce solution
impl Solution {
    pub fn two_sum_bruteforce(nums: Vec<i32>, target: i32) -> Vec<i32> {
        for (i, &a) in nums.iter().enumerate() {
            for (j, &b) in nums.iter().enumerate() {
                if (i != j) && a + b == target {
                    return vec![i as i32, j as i32];
                } 
            }
        }
        return vec![];
    }
}

// hashmap solution
impl Solution {
    pub fn two_sum_hash(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut hm = HashMap::new();

        for (i, &val) in nums.iter().enumerate() {
            hm.insert(val, i as i32);
        }        

        for (i, &val) in nums.iter().enumerate() {
            let look = target - val;
            if let Some(&j) = hm.get(&look) {
                let pos = j as usize;
                if i != pos {
                    return vec![i as i32, j];
                }
            }
        }
        return vec![];
    }
}

// hashmap solution improve
impl Solution {
    pub fn two_sum_hash_2(nums: Vec<i32>, target: i32) -> Vec<i32> {
        
        let mut hm = HashMap::new();
        for (i, &val) in nums.iter().enumerate() {
            let look = target - val;
            if let Some(&j) = hm.get(&look) {
                let mut res = vec![i as i32, j];
                res.sort();
                return res;
            }
            hm.insert(val, i as i32);
        }
        return vec![];
    }
}


fn main() {

    // two sum
    // given nums = [2, 7, 11, 15], target = 9
    // because nums[0] + nums[1] = 2 + 7 = 9
    // return [0, 1]

    assert_eq!(Solution::two_sum_hash_2(vec![2, 7, 11, 15], 9), vec![0, 1]);
}
