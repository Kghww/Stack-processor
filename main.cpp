#include <iostream>

using namespace std;

const int MAX_SIZE = 20000;

struct CharList {
    char c;
    CharList* next;
    CharList(char val, CharList* nxt = nullptr) : c(val), next(nxt) {}
};

struct StackNode {
    CharList* list;
    StackNode* next;
    StackNode(CharList* l, StackNode* n = nullptr) : list(l), next(n) {}
};

struct Number {
    bool is_negative;
    CharList* absolute;
};


void find_prev_and_last(CharList* current, CharList** prev, CharList** last);

void push(StackNode** stack_head, int* stack_size, CharList* l) {
    StackNode* new_node = new StackNode(l, *stack_head);
    *stack_head = new_node;
    (*stack_size)++;
}

CharList* pop(StackNode** stack_head, int* stack_size) {
    if (!*stack_head) return nullptr;
    StackNode* temp = *stack_head;
    CharList* list = temp->list;
    *stack_head = (*stack_head)->next;
    delete temp;
    (*stack_size)--;
    return list;
}

void deleteList(CharList* head) {
    if (!head) return;
    deleteList(head->next);
    delete head;
}

void deleteStack(StackNode** stack_head, int* stack_size) {
    if (!(*stack_head))
        return;
    deleteList(pop(stack_head, stack_size));
    deleteStack(stack_head, stack_size);
}

CharList* copyList(CharList* head) {
    if (!head) return nullptr;
    CharList* new_node = new CharList(head->c); // Kopia bieżącego węzła
    new_node->next = copyList(head->next);
    return new_node;
}


bool is_all_zero(CharList* list) {
    if (!list) return true;
    if (list->c != '0') return false;
    return is_all_zero(list->next);
}

CharList* reverse_list(CharList* current, CharList* prev = nullptr) {
    if (!current) return prev;
    CharList* next_node = current->next;
    current->next = prev; // Odwrócenie wskaźnika
    return reverse_list(next_node, current);
}

CharList* find_first_non_zero(CharList* node) {
    if (!node) return nullptr;
    if (node->c != '0') return node;
    return find_first_non_zero(node->next);
}

CharList* trim_leading_zeros(CharList* head) {
    CharList* first_non_zero = find_first_non_zero(head);

    if (!first_non_zero) {
        return new CharList('0'); // Przypadek: same zera
    }

    return copyList(first_non_zero);
}

Number parse_number(CharList* list) {
    Number num;
    num.is_negative = false;
    num.absolute = nullptr;

    if (!list) return num;

    CharList* copy = copyList(list);
    CharList* last = nullptr;
    CharList* prev = nullptr;

    find_prev_and_last(copy, &prev, &last);

    if (last->c == '-') {
        num.is_negative = true;
        if (copy == last) {
            delete copy;
            num.absolute = nullptr;
        }
        else {
            if (prev) prev->next = nullptr;
            else copy = nullptr;
            delete last;
            num.absolute = copy;
        }
    }
    else {
        num.absolute = copy;
    }

    // Normalizacja: usuwamy nieistotne zera wiodące (w reprezentacji liczby)
    if (num.absolute) {
        num.absolute = reverse_list(num.absolute);
        num.absolute = trim_leading_zeros(num.absolute);
        num.absolute = reverse_list(num.absolute);
    }

    // Jeśli po normalizacji liczba to same zera, zamień na pojedyncze '0'
    if (num.absolute && is_all_zero(num.absolute)) {
        deleteList(num.absolute);
        num.absolute = new CharList('0');
        num.is_negative = false; // -0 staje się 0
    }

    return num;
}

int length(CharList* list) {
    if (!list) return 0;
    return 1 + length(list->next);
}

int compare_digits(CharList* a, CharList* b) {
    if (!a || !b) {
        return 0;
    }

    if (a->next && b->next) {
        int res = compare_digits(a->next, b->next);
        if (res != 0) return res;
    }

    if (a->c < b->c) return -1;
    else if (a->c > b->c) return 1;
    else return 0;
}

int compare_absolute(CharList* a, CharList* b) {
    int a_len = length(a);
    int b_len = length(b);

    if (a_len > b_len) return 1;
    if (a_len < b_len) return -1;

    return compare_digits(a, b);
}

void printList(CharList* list) {
    if (!list)
        return;
    cout << list->c;
    printList(list->next);
}


void print_helper(StackNode* node, int& index) {
    if (!node) return;
    print_helper(node->next, index);
    cout << index << ": ";
    printList(node->list);
    cout << endl;
    index--;
}

void print_stack(StackNode* stack_head, int stack_size) {
    int index = stack_size - 1;
    print_helper(stack_head, index);
}

int parse_number_recursive(CharList* current, int multiplier, int acc) {
    if (!current) return acc;
    int digit = current->c - '0';
    return parse_number_recursive(
        current->next,
        multiplier * 10,
        acc + (digit * multiplier)
    );
}

int parse_number_to_int(CharList* list) {
    if (!list) return 0;
    Number num = parse_number(list);
    int value = parse_number_recursive(num.absolute, 1, 0);
    if (num.is_negative) value = -value;
    deleteList(num.absolute);
    return value;
}

CharList* int_to_list(int code) {
    if (code == 0) {
        return new CharList('0');
    }
    if (code < 0) {
        code = -code;
    }

    int digit = code % 10;
    CharList* node = new CharList('0' + digit);
    code /= 10;

    if (code > 0) {
        node->next = int_to_list(code);
    }

    return node;
}

CharList* find_tail(CharList* node) {
    if (!node->next) return node;
    return find_tail(node->next);
}

StackNode* get_node_recursive(StackNode* current, int steps) {
    if (steps <= 0 || !current) return current;
    return get_node_recursive(current->next, steps - 1);
}

void find_prev_and_last(CharList* current, CharList** prev, CharList** last) {
    if (!current->next) {
        *last = current;
        return;
    }
    *prev = current;
    find_prev_and_last(current->next, prev, last);
}

CharList* add_numbers(CharList* a, CharList* b, int carry) {
    if (!a && !b && carry == 0) return nullptr;
    int add_a = a ? (a->c - '0') : 0;
    int add_b = b ? (b->c - '0') : 0;

    int sum = add_a + add_b + carry;
    int new_carry = sum / 10;
    int digit = sum % 10;
    CharList* node = new CharList('0' + digit);
    node->next = add_numbers(a ? a->next : nullptr, b ? b->next : nullptr, new_carry);
    
    return node;
}

CharList* subtract_numbers(CharList* a, CharList* b, int borrow) {
    if (!a && !b && borrow == 0) return nullptr;

    int sub_a = (a ? a->c - '0' : 0) - borrow;
    int sub_b = b ? b->c - '0' : 0;

    if (sub_a < sub_b) {
        sub_a += 10;
        borrow = 1;
    }
    else {
        borrow = 0;
    }

    int sub = sub_a - sub_b;

    CharList* node = new CharList('0' + (sub));
    node->next = subtract_numbers(a ? a->next : nullptr, b ? b->next : nullptr, borrow);
    return node;
}

int main() {
    char program[MAX_SIZE];
    char input[MAX_SIZE];

    cin.getline(program, MAX_SIZE);
    cin.getline(input, MAX_SIZE);

    StackNode* stack_head = nullptr;
    int stack_size = 0;

    int ip = 0;
    int input_ptr = 0;

    while (program[ip] != '\0') {
        char instr = program[ip];
        switch (instr) {
            case '\'': {
                push(&stack_head, &stack_size, nullptr);
                ip++;
                break;
            }
            case ',': {
                CharList* top = pop(&stack_head, &stack_size);
                deleteList(top);
                ip++;
                break;
            }
            case ':': {
                if (stack_head) {
                    CharList* copy = copyList(stack_head->list);
                    push(&stack_head, &stack_size, copy);
                }
                else {
                    push(&stack_head, &stack_size, nullptr);
                }
                ip++;
                break;
            }
            case ';': {
                if (stack_size >= 2) {
                    StackNode* first = stack_head;
                    StackNode* second = stack_head->next;
                    first->next = second->next;
                    second->next = first;
                    stack_head = second;
                }
                ip++;
                break;
            }
            case '@': {
                if (stack_head) {
                    CharList* a_list = pop(&stack_head, &stack_size);
                    int a = parse_number_to_int(a_list);
                    deleteList(a_list);

                    
                    StackNode* target = get_node_recursive(stack_head, a);
                    CharList* copy = copyList(target->list);
                    push(&stack_head, &stack_size, copy);
                }
                ip++;
                break;
            }
            case '.': {
                char c = input[input_ptr++];
                CharList* new_list = new CharList(c, pop(&stack_head, &stack_size));
                push(&stack_head, &stack_size, new_list);
                ip++;
                break;
            }
            case '>': {
                CharList* list = pop(&stack_head, &stack_size);
                if (list) {
                    cout << list->c;
                    deleteList(list);
                }
                ip++;
                break;
            }
            case '!': {
                CharList* list = pop(&stack_head, &stack_size);
                bool cond = !list || (list->c == '0' && !list->next);
                deleteList(list);
                push(&stack_head, &stack_size, new CharList(cond ? '1' : '0'));
                ip++;
                break;
            }
            case '<': {
                if (stack_size >= 2) {
                    CharList* a_list = pop(&stack_head, &stack_size);
                    CharList* b_list = pop(&stack_head, &stack_size);

                    Number a = parse_number(a_list);
                    Number b = parse_number(b_list);

                    bool result = false;

                    if (b.is_negative) {
                        if (!a.is_negative) {
                            result = true;
                        }
                        else {
                            int cmp = compare_absolute(b.absolute, a.absolute);
                            result = (cmp == 1);
                        }
                    }
                    else {
                        if (a.is_negative) {
                            result = false;
                        }
                        else {
                            int cmp = compare_absolute(b.absolute, a.absolute);
                            result = (cmp == -1);
                        }
                    }

                    deleteList(a_list);
                    deleteList(b_list);
                    deleteList(a.absolute);
                    deleteList(b.absolute);

                    push(&stack_head, &stack_size, new CharList(result ? '1' : '0'));
                }
                ip++;
                break;
            }
            case '=': {
                if (stack_size >= 2) {
                    CharList* a_list = pop(&stack_head, &stack_size);
                    CharList* b_list = pop(&stack_head, &stack_size);

                    Number a = parse_number(a_list);
                    Number b = parse_number(b_list);

                    bool equal = (a.is_negative == b.is_negative) && (compare_absolute(a.absolute, b.absolute) == 0);

                    deleteList(a_list);
                    deleteList(b_list);
                    deleteList(a.absolute);
                    deleteList(b.absolute);

                    push(&stack_head, &stack_size, new CharList(equal ? '1' : '0'));
                }
                ip++;
                break;
            }
            case '~': {
                CharList* list = int_to_list(ip);
                push(&stack_head, &stack_size, list);
                ip++;
                break;
            }
            case '?': {
                if (stack_size >= 2) {
                    CharList* t = pop(&stack_head, &stack_size);
                    CharList* w = pop(&stack_head, &stack_size);
                    int t_num = 0;
                    if (t) {
                        Number num = parse_number(t);
                        t_num = parse_number_to_int(t);
                        deleteList(num.absolute);
                    }
                    deleteList(t);
                    if (w && (w->c != '0' || w->next)) {
                        ip = t_num;
                        deleteList(w);
                        continue;
                    }
                    deleteList(w);
                }
                ip++;
                break;
            }
            case '-': {
                CharList* list = pop(&stack_head, &stack_size);

                if (!list) {
                    push(&stack_head, &stack_size, new CharList('-'));
                }
                else {
                    CharList* last = nullptr;
                    CharList* prev = nullptr;

                    // Znajdź ostatni element i jego poprzednik
                    find_prev_and_last(list, &prev, &last);

                    if (last->c == '-') {
                        // Usuń ostatni element
                        if (prev) {
                            prev->next = nullptr;
                            delete last;
                        }
                        else {
                            // Lista składa się tylko z '-'
                            delete list;
                            list = nullptr;
                        }
                    }
                    else {
                        // Dodaj '-' na końcu
                        last->next = new CharList('-');
                    }
                    push(&stack_head, &stack_size, list);
                }

                ip++;
                break;
            }
            case '^': {
                CharList* list = pop(&stack_head, &stack_size);
                if (list) {
                    CharList* last = nullptr;
                    CharList* prev = nullptr;

                    find_prev_and_last(list, &prev, &last);

                    if (last && last->c == '-') {
                        if (prev) {
                            prev->next = nullptr;
                            delete last;
                        }
                        else {
                            delete list;
                            list = nullptr;
                        }
                    }
                }
                push(&stack_head, &stack_size, list);
                ip++;
                break;
            }
            case '$': {
                CharList* list = pop(&stack_head, &stack_size);
                if (list) {
                    CharList* first = list;
                    CharList* rest = list->next;
                    first->next = nullptr;
                    push(&stack_head, &stack_size, rest);
                    push(&stack_head, &stack_size, first);
                }
                else {
                    push(&stack_head, &stack_size, nullptr);
                    push(&stack_head, &stack_size, nullptr);
                }
                ip++;
                break;
            }
            case '#': {
                CharList* a = pop(&stack_head, &stack_size);
                CharList* b = pop(&stack_head, &stack_size);

                if (!b) {
                    push(&stack_head, &stack_size, a);
                }
                else {
                    CharList* tail = find_tail(b);
                    tail->next = a;
                    push(&stack_head, &stack_size, b);
                }
                ip++;
                break;
            }
            case '&': {
                print_stack(stack_head, stack_size);
                ip++;
                break;
            }
            case '[': {
                CharList* a = pop(&stack_head, &stack_size);
                int code = a ? a->c : 0; // Pobierz kod ASCII pierwszego znaku
                deleteList(a);
                CharList* list = int_to_list(code); // Zamiana na listę cyfr
                push(&stack_head, &stack_size, list);
                ip++;
                break;
            }
            case ']': {
                CharList* a = pop(&stack_head, &stack_size);
                int code = parse_number_to_int(a);
                deleteList(a);
                code %= 256;
                if (code < 0) code += 256;

                push(&stack_head, &stack_size, new CharList(char(code)));
                ip++;
                break;
            }
            case '+': {
                CharList* a = pop(&stack_head, &stack_size);
                CharList* b = pop(&stack_head, &stack_size);

                Number number_a = parse_number(a);
                Number number_b = parse_number(b);

                bool a_neg = number_a.is_negative;
                bool b_neg = number_b.is_negative;

                CharList* a_abs = number_a.absolute;
                CharList* b_abs = number_b.absolute;

                CharList* result_abs = nullptr;
                bool result_neg = false;

                if (a_neg == b_neg) {
                    result_abs = add_numbers(a_abs, b_abs, 0);
                    result_neg = a_neg;
                }
                else {
                    int compare = compare_absolute(a_abs, b_abs);

                    if (compare == 0) {
                        result_abs = new CharList('0');
                    }
                    else if (compare == 1) {
                        result_abs = subtract_numbers(a_abs, b_abs, 0);
                        result_neg = a_neg;
                    }
                    else {
                        result_abs = subtract_numbers(b_abs, a_abs, 0);
                        result_neg = b_neg;
                    }
                }

                Number tmp_num{false, result_abs};
                tmp_num.absolute = trim_leading_zeros(reverse_list(tmp_num.absolute));
                tmp_num.absolute = reverse_list(tmp_num.absolute);
                result_abs = tmp_num.absolute;
                if (result_neg && result_abs) {
                    CharList* tail = find_tail(result_abs);
                    tail->next = new CharList('-');
                }

                deleteList(a);
                deleteList(b);
                deleteList(number_a.absolute);
                deleteList(number_b.absolute);

                push(&stack_head, &stack_size, result_abs);
                ip++;
                break;
            }
            default: {
                CharList* new_list = new CharList(instr, pop(&stack_head, &stack_size));
                push(&stack_head, &stack_size, new_list);
                ip++;
                break;
            }
        }
    }

    deleteStack(&stack_head, &stack_size);


    return 0;
}