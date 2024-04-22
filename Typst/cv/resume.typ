#set page(
    paper: "a4",
    margin: (
        left: 10mm, 
        right: 10mm, 
        top: 10mm, 
        bottom: 10mm
    ),
)

#set text(
    size: 8pt,
)

#set text(
    font: "FiraCode Nerd Font Mono"
)

// #let theme = rgb("#4273B0")
// #let theme = rgb(126, 34, 206)

#import("colors.typ"): *

#let theme = COLOR.sky-700

#let titleSize = 4.2em
#let spacingItems = 1.4em

// Header 



#let TitleName = stack(
        spacing: 1em,
        stack(
            dir: ltr,
            spacing: 1em,
            text(
                size: titleSize,
                [Daniel]
            ),
            text(
                fill: theme,
                size: titleSize,
                [Vieira]
            ),
        ),
        text(
            size: 1.5em,
            [System Engineer]
        )
    )

#let Contato(icon, text) = stack(
    dir: ltr,
    spacing: 0.4em,
    image("icons/" + icon + ".svg", height: 10pt),
    text
)

#let Contatos = stack(
    spacing: 0.4em,
    Contato("phone",[+31 6 2893 7512]),
    Contato("linkedin",[in/danielvie]),
    Contato("github", [danielvie]),
    Contato("website", [me-danielvie.vercel.com]),
    Contato("email", [danielvie\@gmail.com]),
)

#let Header = box(
    stroke: (bottom: 2pt + theme),
    inset: (bottom: .4em),
    grid(
        columns: (8fr, 3fr),
        column-gutter: 2em,
        align(center)[ #stack(
            dir: ltr,
            spacing: 3em,
            image("img/eu-2.png", height: 60pt),
            TitleName
        ) ],
        Contatos,
    )
)

// Main Content
#let Title(txt, theme: theme) = rect(
    radius: 2pt,
    fill: theme,
    text(
        fill: rgb("#fff"),
        txt
    )
)

#let TitleWork(txt, theme: theme) = box(
    width: 100%,
    inset: (left: 10pt),
    stroke: (bottom: 0.8pt + COLOR.gray-400),
    rect(
        radius: (top:3pt),
        fill: theme,
        text(
            fill: rgb("#fff"),
            txt
        )
    )
)

#let ItemLeft(title, text, theme: theme) = stack(
    spacing: 0.7em,
    Title(title, theme: theme),
    par(justify: true)[#text]
)

#let ItemRight(title, text, theme: COLOR.gray-500) = stack(
    spacing: 0.7em,
    TitleWork(title, theme: theme),
    par(justify: true)[#text]
)

// Sidebar
#let Sidebar = stack(
    spacing: 2.5em,
    ItemLeft(
        "about me",
        [
            I am an engineer that believes
            in contributing to the world with
            creativity and innovation. I have a
            strong background working with
            Matlab/ Simulink/C/C++ in the
            Control System context and solid
            programming skills. I have a passion to use engineering to get to
            new solutions and to be involved
            in a challenging environment and
            energetic people.
        ]
    ),
    ItemLeft(
        "personal",
        stack(
            spacing: .5em,
            "Daniel Vieira",
            "Brazil",
            "1985",
        )
    ),
    ItemLeft(
        "skills",
        stack(
            spacing: .5em,
            [Control System, Model Based Design, System Engineering, Software Design],
        )
    ),
    ItemLeft(
        "programming",
        stack(
            spacing: .5em,
            [Matlab/Simulink, Python, C/C++, C\#, Typescript, Git, Linux],
        )
    ),
    ItemLeft(
        "engineering",
        stack(
            spacing: .5em,
            [Control Theory, Flight Dynamics, Orbital Mechanics, Model Based Design, 
             Hardware in The Loop, Data Analysis, Mathematical Modeling],
        )
    ),
    ItemLeft(
        "hobbies",
        stack(
            spacing: .5em,
            [Cycling, Running, Animes, Paragliding, Things that fly],
        )
    ),
    ItemLeft(
        "languages",
        stack(
            spacing: .5em,
            [Portuguese: mother tongue],
            [English: professional],
        )
    )
)

#let WorkTitle( company, role, city) = stack(
    spacing: 0.6em,
    text(
        size: 1.2em,
        weight: "bold",
        [#company, #role]
    ),
    text(
        size: 0.8em,
        weight: "bold",
        [(#city)]
    )
)

#let ItemWork(date, company, role, city, desc) = grid(
    columns: (1fr, 5fr), 
    column-gutter: 1em,
    align(right)[#text(size: 7pt, date)],
    box(
        stroke: (left: 2pt + COLOR.gray-300),
        inset: (left: 4pt),
        stack(
            spacing: 1.2em,
            WorkTitle( company, role, city),
            par(justify: true)[#desc],
        )
    )
)

#let TitleEducation( school, city) = stack(
    spacing: 0.6em,
    text(
        size: 1.2em,
        weight: "bold",
        school
    ),
    text(
        size: 0.8em,
        weight: "bold",
        [(#city)]
    )
)

#let ItemEducation(date, school, city, title, desc) = grid(
    columns: (1fr, 5fr), 
    column-gutter: 1em,
    align(right)[#text(size: 7pt, date)],
    box(
        stroke: (left: 2pt + COLOR.gray-300),
        inset: (left: 4pt),
        stack(
            spacing: 1.2em,
            TitleEducation( school, city),
            title,
            text(
                style: "italic",
                par(justify: true)[#desc]
            ),
        )
    )
)

#let Content = stack(
    spacing: 2.0em,
    ItemRight(
        "work experience",
        stack(
            spacing: spacingItems,
            ItemWork(
                "2021 - current",
                "ICT Group",
                "Software Designer",
                "Eindhoven, NETHERLANDS",
                stack(
                    spacing: 1em,
                    [\- Designed software for the high-tech industry, primarily embedded software developed in C++, Python and C\#],
                    [\- Implemented MBT (Model Based Testing) in Thermofisher, this was integrated in the test pipelines and CI/CD for better software quality.],
                    [\- Collaborated with various teams to understand system requirements, enabling accurate model descriptions and tests reflective of real system behavior.]
                )
            ),
            ItemWork(
                "2012 - 2021",
                "AVIBRAS",
                "Product development Engineer",
                "São José dos Campos, BRAZIL",
                stack(
                    spacing: 1em,
                    [\- Responsible for the design of the guidance and control system for the Brazilian guided rocket.],
                    [\- Interfaced with structure and aerodynamics teams to develop a non-linear simulation in MATLAB/SIMULINK to validate performance analysis and control law design testing.],
                    [\- Aided in procurement of GNC sensors & actuators, ensuring alignment with project specifications and performance constraints.],
                    [\- Assisted Integration teams in Verification & Validation processes for subsystems using Hardware in the Loop (HIL) and SIMULINK simulations to emulate flight scenarios.],
                    [\- Undertook the role of a field engineer during product development campaigns, focusing on mission planning, flight performance analysis, data reduction, and analysis.],
                    [\- Created a Python tool that encapsulates a mathematical model initially developed in Matlab/Simulink, transpiled to C++ code, and then compiled into a Python library for easy non-linear simulations and analysis. This tool is designed for easy distribution to other users, facilitating widespread use and collaboration.],
                )
            ),
            ItemWork(
                "2011 - 2012",
                "INSTITUTE OF AERONAUTIC AND SPACE",
                "Researcher",
                "São José dos Campos, BRAZIL",
                stack(
                    spacing: 1em,
                    [\- Worked as a researcher at the Institute of Aeronautics and Space, focusing on the Satellite Launch Vehicle.],
                    [\- Developed an attitude controller for a spinning second-stage vehicle to engage trajectory using ON-OFF actuators.],
                    [\- Created digital models for integration into Hardware In The Loop (HIL) simulations of the launcher.],
                )
            ),
        )
    ),
    ItemRight(
        "education",
        stack(
            spacing: spacingItems,
            ItemEducation(
                "2019 - Current",
                "Aeronautics Institute of Technology – ITA",
                "São José dos Campos, BRAZIL",
                [Ph.D.: Systems and Control Engineering],
                [Robust Control of Linear Systems with Switched Actuators Subjected to Dwell-Time Constraints],
            ),
            ItemEducation(
                "2012 - 2015",
                "National Institute for Space Research - INPE",
                "São José dos Campos, BRAZIL",
                [Master: Space Mechanics and Control],
                [Robust Control of Linear Systems with Switched Actuators Subjected to Dwell-Time Constraints],
            ),
            ItemEducation(
                "2004 - 2010",
                "Federal University of Uberlândia - UFU",
                "Uberlândia, BRAZIL",
                [Bachelor: Mechatronic Engineering],
                [Robust Control of Linear Systems with Switched Actuators Subjected to Dwell-Time Constraints],
            ),
        )
    )
)

#let Main = grid(
    columns: (1fr, 3fr),
    column-gutter: 0.8em,
    Sidebar,
    box(
        stroke: (left: 1pt + COLOR.gray-300),
        inset: (left: 0.4em),
        Content,
    )
)

#stack(
    spacing: 0.4em,
    Header,
    Main
)