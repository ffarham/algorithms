"""
Problem Statement: Given n number of bricks, determine the number of possible
ways to build a staircase such that:
- each adjacent step differs by at least one
- all steps must contain at least one brick

Solution: DP
"""

def solution(n):
    
    one_dim_stair_case = [1] + [0]*n
    for brick in range(1,n+1):
        for height in range(n,brick-1,-1):
            one_dim_stair_case[height] += one_dim_stair_case[height-brick]
    return one_dim_stair_case[-1]-1

def main():
    
    for i in range(3,10):
        possible_staircases = solution(i)
        print(f"{' '*(i<=9)+str(i)}: {possible_staircases}")
    

if __name__ == "__main__":
    main()