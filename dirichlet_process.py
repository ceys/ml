import random


def chinese_restaurant_process(num_customers, alpha):
    if num_customers <= 0:
        return []
        
    table_assignments = [1]
    next_open_table = 2

    for i in range(1, num_customers):
        if random.random() < float(alpha) / (alpha + i):
            table_assignments.append(next_open_table)
            next_open_table += 1
        else:
            which_table = table_assignments[random.randint(0,len(table_assignments))-1]
            table_assignments.append(which_table)

    return table_assignments


def polya_urn_model(num_balls, alpha, base_color_distribution=lambda :round(random.random(),2)):
    if num_balls <= 0:
        return []

    balls_in_urn = []

    for i in range(0, num_balls):
        if random.random() < float(alpha) / (alpha + len(balls_in_urn)):
            new_color = base_color_distribution()
            balls_in_urn.append(new_color)
        else:
            ball = balls_in_urn[random.randint(0, len(balls_in_urn))-1]
            balls_in_urn.append(ball)

    return balls_in_urn


def stick_breaking_process(num_weights, alpha):
    if num_weights <= 0:
        return []

    weights = []
    betas = [0]
    remaining_stick_length = 1

    for i in range(0, num_weights):
        #beta = random.betavariate(num_weights/(1+alpha), num_weights*alpha/(1+alpha))
        beta = random.betavariate(1, alpha)
        betas.append(beta)
        remaining_stick_length = (1 - betas[i]) * remaining_stick_length
        weight = remaining_stick_length * beta
        weights.append(weight) 

    return weights

