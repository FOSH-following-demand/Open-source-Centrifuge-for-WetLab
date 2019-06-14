# An Open Source Centrifuge Design for wetlab

## Hi! 😄 Welcome to the project
We are working on the design of an open hardware centrifuge based on the following questions:
- What can be improved in existing commercial centrifuges?
- What can be improved in already existing open hardware models?
- **Goal:** Design, improve a key feature based on the answers we got from these two questions.
#### Design approach:
- Replicate a model of open hardware centrifuges.
- Reverse engineer existing broken commercial centrifuges (fix them is possible as part of the process of learning how they work how, and how they can be improved).
- Propose and develop improvements.
    - Currently there are improvements to be made with regard to cooling and safety.

For more information on how we are tackling improvements, ideas, developments [look at the tests-experiments we are working on.](https://github.com/FOSH-following-demand/Open-source-Centrifuge-for-WetLab/tree/master/R%26D/test-cards)

### Current status of the project:
- [Collected data from users](https://docs.google.com/forms/d/1zq9jXL4ni4LQY3pLsI8-8exPlcGnMdUV0iULsLTLMks/viewanalytics). This one already points to interesting features to focus on that open hardware solutions don't consider like cooling, or automatic check  of proper balancing.
- [Ordered parts of Polyfuge version.](https://github.com/FOSH-following-demand/Open-source-Centrifuge-for-WetLab/blob/master/R%26D/Polyfuge-BOM.yml).

### Current phase: Concept generation and prototype design
Based on the research done about centrifuge usage we have defined [requirements](https://github.com/FOSH-following-demand/Open-source-Centrifuge-for-WetLab/tree/master/R%26D/Analysis) and target features to focus on.
## Links
- [Concept for solutions and test cards.](https://github.com/FOSH-following-demand/Open-source-Centrifuge-for-WetLab/tree/master/R%26D/test-cards)
- Find out the concept and associated test cases here.

## About project documentation and folders:
There are two sets of documentation in this repository:
- One that is external and relevant for users. This we try to document carefully and make it easy to understand to others outside the core team. Our final project documentation(the source) will be presented in [this format](https://fosh-following-demand.github.io/Open-source-Centrifuge-for-WetLab/). Be aware that is currently not finished as we haven't released the results yet.
- Another set of documentation is where we keep internal track of our tasks and progress. This one might be too detailed for external users, and even contributors. If you are interested in following up also this set of documentation you need to:
  - Use Atom editor.
  - And install the [.imdone](https://atom.io/packages/imdone-atom) package in Atom.
  - Clone the project.
  - Press `Alt+P`, and you should see the status of project management, tasks and priorities.

## References:
- [Value Proposition prototyping and testing](https://issuu.com/business.model.innovation/docs/vpd_sneakpeek/92)


# Progress documentation
| Week        | Products           | Call  | Status |
| ----------- | ------------------ | ----- |--------|
| Week 1      | GitHub repo + related_work.md + draft BoM          | 1st call with mentor  | Done
|             | Went to the lab and did usage research with scientist      |         |            |
| Week 2      | Order BoM + Dev Plan          | 2nd call with mentor  | Done |
|          | Designed and sent form based on Usage analysis                    |                 |      Done                |
| Week 3     | Updates on development          | 3rd call with mentor  | Done |
|            | Collecting Data and studying other models (of big and small centrifuges) |                |         |
|  |Development planned updated, Concept generation | Not able to build because of delayed delivery of components | |
| Week 4     | Got enough results to focus on two key issues: safety and cooling, as we haven't found an open hardware solution with cooling mechanism. Safety and balancing still can be improved in the commercial centrifuges we analyzed          | 4th called with mentor  | Done |
| Week 5  | Documenting new concepts and test cases, and updating ordering lists | 5th mentor called    |Done|
| Week 6  | Architecture layout for peltier module, teard down and printing of polyfuge parts | 5th mentor called    ||
