#include "person.h"

#include <numeric>
#include <ranges>
#include <utility>

Person::Person(std::string name, const Age age, const Salary salary)
    : name_(std::move(name)), age_(age.value), salary_(salary.value) {}

double calculate_average_eligible_salary_ranges(
    const std::vector<Person>& people, int age_threshold, double min_salary) {
  // Pipeline: filter -> transform (salary) -> accumulate
  auto eligible_salaries_view =
      people |
      std::views::filter([age_threshold, min_salary](const Person& person) {
        return person.get_age() >= age_threshold &&
               person.get_salary() > min_salary;
      }) |
      std::views::transform(
          [](const Person& person) { return person.get_salary(); });

  const double total_eligible_salary = std::accumulate(
      eligible_salaries_view.begin(), eligible_salaries_view.end(), 0.0);

  // To get the count, we count the view elements directly. For more about
  // the double-long usage, please refer to this SO post:
  // https://stackoverflow.com/a/62132391/2748860
  const int64_t count = std::ranges::distance(eligible_salaries_view);

  if (count == 0) {
    return 0.0;
  }

  return total_eligible_salary / static_cast<double>(count);
}
