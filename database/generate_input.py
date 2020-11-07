import random
import argparse

# ------------------------------------------------- CONSTS -------------------------------------------------------------
VALUE_SEP = ','
RECORD_SEP = ';'
SERIES_NUMBER = -1
LENGTH_NUMBER = -1


# ----------------------------------------------- MAIN BODY ------------------------------------------------------------
def generate(params):
    """
    Generate file to sort

    :param params:
        params.output
        params.series
        params.length
    """

    try:
        output = open(params.output, 'w')
    except FileNotFoundError as e:
        print('File not found in given path: {0}. Error: {1}'.format(params.output, e))
        raise

    # Number of series in file
    s: int = params.series if params.series > 0 else random.randint(3, 1000000)
    print('Saving {0} series to file...'.format(s))
    for _ in range(s):
        # values to append to file
        val1: int = random.randint(0, 100)
        # val2: int = random.randint(0, 100)
        val2: int = val1

        # Number of records in series
        l: int = params.length if 1 < params.length < 50 else random.randint(2, 20)
        for _ in range(l):
            inc: int = random.randint(100, 500)
            output.write(str(val1) + VALUE_SEP)
            output.write(str(val2) + RECORD_SEP)
            val1 += inc
            val2 += inc

    print('Saved successfully'.format(s))
    output.close()


# ----------------------------------------------- PARAMETERS -----------------------------------------------------------
if __name__ == '__main__':
    # params to set in console script
    parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    # path to csv file with records to generate
    parser.add_argument('--output', type=str, required=True,
                        help='Path to output file')
    # Minimum value to remove from words
    parser.add_argument('--series', type=int, default=SERIES_NUMBER,
                        help='Number of series in file, default is random')
    # If true data will be sorted alphabetically
    parser.add_argument('--length', type=int, default=LENGTH_NUMBER,
                        help='Length of series (min 2, max 50), default is random')

    params = parser.parse_args()
    generate(params)
