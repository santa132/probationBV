def minDenominations(denominations, amount_money):
    try:
        # Base case: if V is 0, return 0
        if amount_money == 0:
            return []

        # Initialize result
        res = float('inf')
        min_denominations = []

        for deno in denominations:
            if deno <= amount_money:
                # Recursive call to find minimum coins for remaining value
                sub_res = minDenominations(denominations, amount_money - deno)

                # Update result if sub-result is valid and less than current result
                if sub_res is not None and len(sub_res) + 1 < res:
                    res = len(sub_res) + 1
                    min_denominations = sub_res + [deno]

        if min_denominations:
            return min_denominations
        else:
            return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def verifyDenoMoney(denominations, amount_money):
    for deno in denominations:
        if deno <= 0:
            raise ValueError("Denominations must be positive.")
    if amount_money <= 0:
        raise ValueError("Amount money must be positive.")
    return True

if __name__ == "__main__":
    try:
        denominations = list(map(int, input("Enter coin denominations: ").split()))
        amount_money = int(input("Enter amount money: "))
        verifyDenoMoney(denominations, amount_money)

        min_denominations = minDenominations(denominations, amount_money)

        if min_denominations is not None:
            print("Minimum denomination is", len(min_denominations), "with denominations:", sorted(min_denominations))
        else:
            print("It is not possible to make change for the given value using the provided coin denominations.")
    except Exception as e:
        print(f"An error occurred: {e}")
