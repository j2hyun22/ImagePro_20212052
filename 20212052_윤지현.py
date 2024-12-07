import random
from typing import List, Dict

# 학생 정보 생성 함수
def generate_students(num_students: int) -> List[Dict[str, int]]:
    students = []
    for _ in range(num_students):
        name = ''.join(random.choices('ABCDEFGHIJKLMNOPQRSTUVWXYZ', k=2))
        age = random.randint(18, 22)
        score = random.randint(0, 100)
        students.append({"이름": name, "나이": age, "성적": score})
    return students

# 선택 정렬
def selection_sort(data: List[Dict[str, int]], key: str, verbose: bool = False) -> List[Dict[str, int]]:
    arr = data[:]
    for i in range(len(arr)):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[j][key] < arr[min_idx][key]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
        if verbose:
            print(f"Step {i + 1}: {arr}")
    return arr

# 삽입 정렬
def insertion_sort(data: List[Dict[str, int]], key: str, verbose: bool = False) -> List[Dict[str, int]]:
    arr = data[:]
    for i in range(1, len(arr)):
        current = arr[i]
        j = i - 1
        while j >= 0 and arr[j][key] > current[key]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = current
        if verbose:
            print(f"Step {i}: {arr}")
    return arr

# 퀵 정렬
def quick_sort(data: List[Dict[str, int]], key: str, verbose: bool = False, step: List[int] = [0]) -> List[Dict[str, int]]:
    if len(data) <= 1:
        return data
    pivot = data[0]
    less = [x for x in data[1:] if x[key] <= pivot[key]]
    greater = [x for x in data[1:] if x[key] > pivot[key]]
    sorted_less = quick_sort(less, key, verbose, step)
    sorted_greater = quick_sort(greater, key, verbose, step)
    result = sorted_less + [pivot] + sorted_greater
    if verbose:
        step[0] += 1
        print(f"Step {step[0]}: {result}")
    return result

# 기수 정렬 (성적 기준으로만 사용)
def radix_sort(data: List[Dict[str, int]], verbose: bool = False) -> List[Dict[str, int]]:
    arr = data[:]
    max_score = max(student["성적"] for student in arr)
    exp = 1
    step = 0
    while max_score // exp > 0:
        buckets = [[] for _ in range(10)]
        for student in arr:
            index = (student["성적"] // exp) % 10
            buckets[index].append(student)
        arr = [student for bucket in buckets for student in bucket]
        exp *= 10
        step += 1
        if verbose:
            print(f"Step {step}: {arr}")
    return arr

# 메뉴 표시 및 사용자 입력 처리
def menu():
    print("\n정렬 메뉴:")
    print("1. 이름을 기준으로 정렬")
    print("2. 나이를 기준으로 정렬")
    print("3. 성적을 기준으로 정렬")
    print("4. 프로그램 종료")

# 메인 프로그램
def main():
    students = generate_students(30)
    print("생성된 학생 정보:")
    for student in students:
        print(student)
    
    while True:
        menu()
        choice = input("선택하세요 (1-4): ")
        if choice == "4":
            print("프로그램을 종료합니다.")
            break
        key_map = {"1": "이름", "2": "나이", "3": "성적"}
        if choice not in key_map:
            print("잘못된 입력입니다. 다시 시도하세요.")
            continue
        
        key = key_map[choice]
        print("\n정렬 알고리즘:")
        print("1. 선택 정렬")
        print("2. 삽입 정렬")
        print("3. 퀵 정렬")
        if choice == "3":  # 성적 정렬 시 기수 정렬 추가
            print("4. 기수 정렬")
        
        algo_choice = input("알고리즘을 선택하세요 (1-4): ")
        if algo_choice == "4" and choice != "3":
            print("기수 정렬은 성적 정렬에서만 사용 가능합니다.")
            continue

        verbose = input("단계별 출력을 보시겠습니까? (y/n): ").lower() == "y"
        
        if algo_choice == "1":
            sorted_students = selection_sort(students, key, verbose)
        elif algo_choice == "2":
            sorted_students = insertion_sort(students, key, verbose)
        elif algo_choice == "3":
            sorted_students = quick_sort(students, key, verbose)
        elif algo_choice == "4" and choice == "3":
            sorted_students = radix_sort(students, verbose)
        else:
            print("잘못된 입력입니다. 다시 시도하세요.")
            continue

        print("\n정렬된 학생 정보:")
        for student in sorted_students:
            print(student)

if __name__ == "__main__":
    main()
