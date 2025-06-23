#include "person.h"

#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

Person::Person(std::string name, const int age, const double salary)
    : name(std::move(name)), age(age), salary(salary) {}

double calculate_average_eligible_salary_ranges(
    const std::vector<Person>& people, int age_threshold, double min_salary) {
  // Pipeline: filter -> transform (salary) -> accumulate
  auto eligible_salaries_view =
      people | std::views::filter([age_threshold, min_salary](const Person& p) {
        return p.get_age() >= age_threshold && p.get_salary() > min_salary;
      }) |
      std::views::transform([](const Person& p) { return p.get_salary(); });

  const double total_eligible_salary = std::accumulate(
      eligible_salaries_view.begin(), eligible_salaries_view.end(), 0.0);

  // To get the count, we count the view elements directly
  const long count = std::ranges::distance(eligible_salaries_view);

  if (count == 0) {
    return 0.0;
  }

  return total_eligible_salary / static_cast<double>(count);
}
