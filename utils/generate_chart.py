import matplotlib.pyplot as plt

# CONSTS ---------------------------------------------------------------------------------------------------------------
PHASE_X = [10, 100, 1000, 10000, 100000, 1000000, 10000000]
PHASE_Y = [3, 8, 13, 18, 23, 27, 32]

PHASE_THEORETICAL_X = [10, 100, 1000, 10000, 100000, 1000000, 10000000]
PHASE_THEORETICAL_Y = [4, 9, 14, 18, 23, 28, 33]

INOUT_X = [10, 100, 1000, 10000, 100000, 1000000, 10000000]
INOUT_Y = [10, 20, 70, 794, 9802, 114390, 1339234]

INOUT_T_X = [10, 100, 1000, 10000, 100000, 1000000, 10000000]
INOUT_T_Y = [1, 4, 57, 761, 9515, 114208, 1332867]

BLOCK_SIZE = 4096


# FUNCTIONS ------------------------------------------------------------------------------------------------------------
def _print_data(x_array: [], y_array: [], x_t_array: [], y_t_array: [], title: str):
    """
    :param x_array: All x values data
    :param y_array: All y values data
    :param title: Graph title
    :param print_points: Boolean tell to print or not interpolated points
    :param do_scale: Scale graph
    """

    # plt.xscale('log')
    # plt.yscale('log')
    plt.plot(x_t_array, y_t_array, color='orange', label='Theoretical number')
    plt.plot(x_array, y_array, label='Result in sort')

    plt.ylabel('Number of reads/writes')
    plt.xlabel('Number of records')
    plt.title(title)
    plt.legend()
    plt.show()


# _print_data(PHASE_X, PHASE_Y, PHASE_THEORETICAL_X, PHASE_THEORETICAL_Y,
#             f'Compare theoretical phase number\n with sort result for {BLOCK_SIZE}bytes block size  (log xscale)')

_print_data(INOUT_X, INOUT_Y, INOUT_T_X, INOUT_T_Y,
            f'Compare theoretical read/write operations number\n with sort result for {BLOCK_SIZE}bytes block size')
