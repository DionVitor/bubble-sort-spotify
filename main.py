from datetime import datetime


magic_dict = {}

with open("reviews.csv", "r") as reviews_file:
    # Skip heading
    heading = next(reviews_file)

    for row in reviews_file:
        time_submitted_and_rating = row.split(";")
        date = datetime.strptime(time_submitted_and_rating[0], "%Y-%m-%d %H:%M:%S")
        formated_date = date.strftime("%Y-%m")

        if not magic_dict.get(formated_date):
            magic_dict[formated_date] = {
                "sum": int(time_submitted_and_rating[1]),
                "count": 1
            }
        else:
            magic_dict[formated_date]["sum"] += int(time_submitted_and_rating[1])
            magic_dict[formated_date]["count"] += 1

with open("output.csv", "a+") as output_file:
    output_file.write("year-mounth,media\n")
    for key, value in magic_dict.items():
        output_file.write(f"{key}, {value['sum'] / value['count']}\n")
