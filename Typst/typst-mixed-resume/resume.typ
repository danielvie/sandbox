
#import "template.typ": *

#set page(
    margin: (
        left: 10mm, 
        right: 10mm, 
        top: 15mm, 
        bottom: 15mm
    ),
)

#set text(font: "Mulish")

#show: project.with(
    // theme: rgb(73%, 1%, 0%, 4%),
    theme: rgb("#4273B0"),
    first_name: "Daniel",
    last_name: "Vieira",
    title: "System Engineer",
    contact: (
        contact(
            text: "(+31) 6 2893 7512",
            type: "phone",
        ),
        contact(
            text: "in/danielvie", 
            link: "https://www.linkedin.com/in/danielvie/",
            type: "linkedin",
        ),
        contact(
            text: "danielvie", 
            link: "https://www.github.com/danielvie",
            type: "github",
        ),
        contact(
            text: "me-danielvie.vercel.com", 
            link: "https://me-danielvie.vercel.com",
            type: "website",
        ),
        contact(
            text: "danielvie@gmail.com", 
            link: "mailto:danielvie@gmail.com",
            type: "email",
        ),
    ),
    main: (
        section(
            title: "Work Experience",
            content: (
                subSection(
                    title: "Site Reliability Engineer",
                    titleEnd: "Engineering Dept., " + lorem(3),
                    subTitle: "May 2021 – Present",
                    subTitleEnd: "New York, US",
                    content: list(
                        [#lorem(15)],
                        [#lorem(17)],
                        [#lorem(19)],
                    ),
                ),
                subSection(
                    title: "Senior Engineer",
                    titleEnd: "XXX Division, " + lorem(2),
                    subTitle: "May 2020 – May 2021",
                    subTitleEnd: "Toyko, Japen",
                    content: list(
                        [#lorem(15)],
                        [#lorem(17)],
                        [#lorem(19)],
                    ),
                ),
            ),
        ),
        section(
            title: "Projects",
            content: (
                subSection(
                    title: "Personal project I",
                    titleEnd: "",
                    subTitle: "",
                    subTitleEnd: "",
                    content: list(
                        [#lorem(15)],
                        [#lorem(17)],
                        [#lorem(19)],
                    ),
                ),
                subSection(
                    title: "Personal project II",
                    titleEnd: "",
                    subTitle: "",
                    subTitleEnd: "",
                    content: list(
                        [#lorem(15)],
                        [#lorem(17)],
                        [#lorem(19)],
                    ),
                ),
            ),
        ),
    ),
    sidebar: (
        section(
            title: "about me",
            content: (
                subSection(
                    content: 
                        [I am an engineer that believes in contributing to the world with 
                        creativity and innovation. I have a strong background working with Matlab/
                        Simulink/C/C++ in the Control System context and solid 
                        programming skills. I have a passion to use engineering to get to 
                        new solutions and to be involved in a challenging environment and energetic people.],
                ),
            ),
        ),
        section(
            title: "skills",
            content: (
                subSection(
                    title: "MEng",
                    subTitle: "2018 – 2020",
                    subTitleEnd: "Stanford Univ.",
                ),
                subSection(
                    title: "BSc",
                    titleEnd: "Computer Science",
                    subTitle: "2014 – 2018",
                    subTitleEnd: "National Taiwan Univ.",
                ),
            ),
        ),
            section(
            title: "Awards",
            content: (
                subSection(
                    content: list( "Certified Kubernetes Administrator",),
                ),
            ),
        ),
        section(
            title: "Contributions",
            content: (
                subSection(
                    title: "Typst maintainer",
                    subTitleEnd: underline(link("https://github.com/typst/typst", "typst")),
                ),
                subSection(
                    title: "Bug reporting and fix",
                    subTitleEnd: underline(link("https://github.com/microsoft/vscode-python/issues", "vscode-python")),
                ),
            ),
        ),

         section(
            title: "Articles",
            content: (
                subSection(
                    content: list(
    underline(lorem(10)),
    underline(lorem(9)),
    underline(lorem(8)),
                    ),
                ),
            ),
        ),
    ),
)
