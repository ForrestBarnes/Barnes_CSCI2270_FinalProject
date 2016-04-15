This project is designed to take, modify, and (when requested) output the structure of an organization.

The primary requirement of the structure is that the organization MUST have a CEO. If no CEO is given or no CEO can be found, this project will do nothing until the user inputs the name of a CEO. When the program starts, creating a CEO is the first thing a user must do.

The remainder of this project is fairly self-explanatory, but I will outline it anyway:
1. For every person in the organization, there is a list of people who report directly to them, ordered by seniority.
2. Every person in the organization has one group they are a part of and a role within that group.
	A. The CEO's group is always Management.
	B. In every group, there is always one person whose role is "Head". This role is always given to the most senior person in the group.
	C. When a new employee is added, they automatically take on the group of their employer. Their role is blank until modified.
3. When a person is fired, their most senior employee is promoted into their place. As in 4, all people reporting to that most senior employee are also promoted, but they are now the least senior people reporting to that employee.
4. Anyone not in senior management (CEO or directly reporting to the CEO) can be promoted. This promotion moves them and their entire group up one level in the organization. To be speciific, the promoted person becomes their previous boss's boss's least senior employee.
All names of groups and people in the organization must be unique.
