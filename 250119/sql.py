
# 1. Active Monthly Price for Subscriptions
# Given a table with user_id, start_date, end_date, and price, compute the active monthly price per user.
# Assume:
# end_date can be NULL, meaning the subscription is still active.
# Some users may have multiple subscriptions in the same month.

# Example Table:
# | user_id | start_date  | end_date    | price  |
# |---------|------------|------------|--------|
# | 1       | 2023-01-10 | 2023-03-15 | 10.00  |
# | 1       | 2023-02-01 | NULL       | 20.00  |
# | 2       | 2023-03-05 | 2023-05-20 | 15.00  |

# Expected Output:
# | user_id | year | month | avg_monthly_price |
# |---------|------|-------|-------------------|
# | 1       | 2023 | 01    | 10.00             |
# | 1       | 2023 | 02    | 15.00             |
# | 1       | 2023 | 03    | 20.00             |
# | 2       | 2023 | 03    | 15.00             |

# SELECT 
#     user_id, 
#     EXTRACT(YEAR FROM start_date) AS year, 
#     EXTRACT(MONTH FROM start_date) AS month, 
#     AVG(price) AS avg_monthly_price
# FROM subscriptions
# WHERE (end_date IS NULL OR end_date >= CURDATE()) 
# GROUP BY user_id, year, month
# ORDER BY user_id, year, month;


# 2. Query with JOINS & GROUP BY
# Write an SQL query that:

# Joins two tables (users and subscriptions).
# Groups by user_id.
# Finds the total revenue per user for the last 6 months.
# Tables:
# users
# | user_id | name    |
# |---------|--------|
# | 1       | Alice  |
# | 2       | Bob    |

# subscriptions
# | user_id | start_date  | end_date    | price  |
# |---------|------------|------------|--------|
# | 1       | 2023-01-01 | 2023-06-01 | 10.00  |
# | 1       | 2023-07-01 | NULL       | 15.00  |
# | 2       | 2023-02-10 | 2023-12-31 | 20.00  |

# Expected Output:
# | user_id | name  | total_revenue_last_6_months |
# |---------|------|----------------------------|
# | 1       | Alice | 25.00                      |
# | 2       | Bob   | 20.00                      |

# SELECT 
#     s.user_id, 
#     u.name, 
#     SUM(s.price) AS total_revenue_last_6_months
# FROM subscriptions s
# JOIN users u ON s.user_id = u.user_id
# WHERE s.start_date >= DATE_SUB(CURDATE(), INTERVAL 6 MONTH)
# GROUP BY s.user_id, u.name
# ORDER BY total_revenue_last_6_months DESC;