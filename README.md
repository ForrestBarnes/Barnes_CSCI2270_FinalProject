This project is designed to take, modify, and (when requested) output the structure of an organization.

The primary requirement of the structure is that the organization MUST have a CEO. If no CEO is given or no CEO can be found, this project will do nothing until the user inputs the name of a CEO. When the program starts, creating a CEO is the first thing a user must do.

The remainder of this project is fairly self-explanatory, but I will outline it anyway:
1. For every person in the organization, there is a list of people who report directly to them, ordered by seniority.
2. When a person is removed from the organization, everyone who reports to them becomes the least senior employees of their removed person's boss, unless the removed person is the CEO. If the CEO is removed, their most senior employee becomes CEO and all people who report to that person become their least senior employees, after the former CEO's employees.
3. Any person can be moved from one position to another, though they will not retain their employees if you do so. (Their employees will be promoted instead)
	a. No person can be moved directly to CEO status.
4. Anyone but the CEO can be promoted. When this happens, every employee of that person stays an employee of that person and is effecively promoted as well.
	a. If the person is promoted into the position of CEO, the old CEO becomes their most senior employee and gets all of their old employees. This makes senior management a more isolated community.

All names must be unique.
All names must be at least two characters long.
All names must only contain alphanumerics, spaces, or dashes.