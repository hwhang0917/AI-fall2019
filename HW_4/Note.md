* ### getAttackScore()

  * ####  Row conflict calculation

    If there are **n** number of queens in the same row, there are following amount of conflicts:
    $$
    (n(n-1)/2)
    $$

  * #### Column conflict calculation

    Will not happen in our case, because there are 1 queen per column.

  * #### Diagonal conflict calculation

    Following is a 8x8 chess board:

    |       |  0   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |
    | :---: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
    | **7** |  7   |  8   |  9   |  10  |  11  |  12  |  13  |  14  |
    | **6** |  6   |  7   |  8   |  9   |  10  |  11  |  12  |  13  |
    | **5** |  5   |  6   |  7   |  8   |  9   |  10  |  11  |  12  |
    | **4** |  4   |  5   |  6   |  7   |  8   |  9   |  10  |  11  |
    | **3** |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  10  |
    | **2** |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |
    | **1** |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |
    | **0** |  0   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |

    The **diagonal_id** can be computed by adding **row_id** + **column_id**

    However, in the case of diagonal, there can be two ways of diagonal line that can be drawn:

    |       |  0   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |
    | :---: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
    | **0** |  0   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |
    | **1** |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |
    | **2** |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |
    | **3** |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  10  |
    | **4** |  4   |  5   |  6   |  7   |  8   |  9   |  10  |  11  |
    | **5** |  5   |  6   |  7   |  8   |  9   |  10  |  11  |  12  |
    | **6** |  6   |  7   |  8   |  9   |  10  |  11  |  12  |  13  |
    | **7** |  7   |  8   |  9   |  10  |  11  |  12  |  13  |  14  |

    Same way as row conflict, if there are **n** number of queens in the same diagonal line, there are following amount of conflicts:

  $$
  (n/(n-1)/2)
  $$

