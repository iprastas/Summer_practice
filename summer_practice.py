import re
import itertools
import time

def solve(rebus):
    words = re.findall('[A-Z]+', rebus.upper()) #из строки выбираем слова
    unique_let = set(''.join(words)) # выбираем множество уникальных букв
    
    assert len(unique_let) <= 10, 'Различных букв больше 10. Невозможно зашифровать однозначно.' # исключение, если букв больше 10

    first_let = {word[0] for word in words} # выбираем первые буквы трех слов

    n = len(first_let)
    sorted_let = ''.join(first_let) + \
        ''.join(unique_let - first_let) #в одну строку + первые буквы слов в начало

    letters = tuple(ord(c) for c in sorted_let) #числовое представление для указанного символа
    digits = tuple(ord(c) for c in '0123456789') #числовое представление для указанного символа
    zero = digits[0]

    for guess in itertools.permutations(digits, len(letters)):
        
        if zero not in guess[:n]: #если не первые буквы слов (чтоб не равнялись 0)
            equation = rebus.translate(dict(zip(letters, guess))) #вместо букв подставляем цифры

            if eval(equation): # вычисляем
                return equation


start_time = time.time()
print('BB + BB == ABC')
print(solve('BB + BB == ABC'))
print("--- %s seconds ---\n" % (time.time() - start_time))

start_time = time.time()
print('SEND + MORE == MONEY')
print(solve('SEND + MORE == MONEY'))
print("--- %s seconds ---\n" % (time.time() - start_time))

start_time = time.time()
print('SATURN + URANUS == PLANETS')
print(solve('SATURN + URANUS == PLANETS'))
print("--- %s seconds ---\n" % (time.time() - start_time))
