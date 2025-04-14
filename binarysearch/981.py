"""
LeetCode Problem 981: Time Based Key-Value Store
Difficulty: Medium

Problem Description:
Design a time-based key-value data structure that can store multiple values for the same key at different time stamps 
and retrieve the key's value at a certain timestamp.

Implement the TimeMap class:

    - TimeMap() 
        Initializes the object of the data structure.
    
    - void set(String key, String value, int timestamp) 
        Stores the key with the value at the given timestamp.
    
    - String get(String key, int timestamp) 
        Returns a value such that set was called previously with timestamp_prev <= timestamp.
        If multiple such values exist, returns the value associated with the largest timestamp_prev.
        If there are no suitable values, return "".

Example 1:
Input:
["TimeMap", "set", "get", "get", "set", "get", "get"]
[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]

Output:
[null, null, "bar", "bar", null, "bar2", "bar2"]

Explanation:
TimeMap timeMap = new TimeMap()
timeMap.set("foo", "bar", 1)       # stores "foo" = "bar" at timestamp 1
timeMap.get("foo", 1)              # returns "bar"
timeMap.get("foo", 3)              # returns "bar"
timeMap.set("foo", "bar2", 4)      # stores "foo" = "bar2" at timestamp 4
timeMap.get("foo", 4)              # returns "bar2"
timeMap.get("foo", 5)              # returns "bar2"

Constraints:
- 1 <= key.length, value.length <= 100
- key and value consist of lowercase English letters and digits
- 1 <= timestamp <= 10^7
- All timestamps of set calls are strictly increasing
- At most 2 * 10^5 calls will be made to set and get
"""

class Entry(object):

    def __init__(self, timestamp, val):
        self.entries = []
        self.timestamps = []

        self.timestamps.append(timestamp)
        self.entries.append(val)
    
    def add_entry(self, timestamp, val):

        self.entries.append(val)
        self.timestamps.append(timestamp)

class TimeMap(object):

    def __init__(self):
        self.map = {}
        

    def set(self, key, value, timestamp):
        """
        :type key: str
        :type value: str
        :type timestamp: int
        :rtype: None
        """
        # dont have a dict inside a dict or you will hit TLE
        if key in self.map:
            self.map[key].add_entry(timestamp, value)
        
        else:
            newEntry = Entry(timestamp, value)
            self.map[key] = newEntry
        

    def get(self, key, timestamp):
        """
        :type key: str
        :type timestamp: int
        :rtype: str
        """
        ret = ""
        if key in self.map:
            entry_obj = self.map[key]
            ret = self.binarySearch(entry_obj.timestamps, timestamp, entry_obj.entries)
        return ret
    
    def binarySearch(self, arr, target, values):
        arrLen = len(arr)
        left = 0
        right = arrLen - 1

        mid = left + (right - left) // 2

        ret = ""

        while (left <= right):

            if arr[mid] > target:
                right = mid - 1
                mid = left + (right - left) // 2
            elif arr[mid] <= target: # get the closest timestamp iteratively
                ret = values[mid]
                left = mid + 1
                mid = left + (right - left) // 2
        return ret


        


# Your TimeMap object will be instantiated and called as such:
# obj = TimeMap()
# obj.set(key,value,timestamp)
# param_2 = obj.get(key,timestamp)