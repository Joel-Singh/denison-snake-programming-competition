#import "@preview/hydra:0.6.2": hydra

#let heading_page_break = state("heading_page_break", true)

#let main-color = green.darken(20%)

#let general(
  class: "",
  title: "",
  preamble: "",
  note_space: false,
  blank_pages: 0,
  professional: false,
  title_pagebreak: true,
  include_outline: true,
  include_line: true,
  header_extra: "",
  doc,
) = [
  #let base_header_left = [
    Joel Singh
  ]
  #let base_header_right = [
    #class
  ]

  #let main-color = if professional {
    black
  } else {
    main-color
  }

  #let first-header = state("first-header", true)
  #set page(
    paper: "us-letter",
    margin: 1in,
    header: context {
      {
        if first-header.get() {
          first-header.update(false)
          set text(fill: main-color)
          base_header_left
          h(1fr)
          header_extra
          h(1fr)
          base_header_right
        } else {
          {
            set text(fill: main-color.lighten(40%))
            base_header_left
          }
          h(1fr)
          {
            set text(fill: main-color)
            emph(hydra(1, skip-starting: false))
          }
          h(1fr)
          {
            set text(fill: main-color.lighten(40%))
            base_header_right
          }
        }
      }
    },
    numbering: "1/1",
  )


  #set par(first-line-indent: 1.8em, justify: true)
  #set text(font: "New Computer Modern")
  #show raw: set text(font: "New Computer Modern Mono")
  #show heading: set block(above: 1.4em, below: 1em)
  #set list(marker: text(
    fill: main-color,
  )[#sym.triangle.filled.r])
  #set math.mat(delim: "|")
  #set grid(gutter: 1em)
  #set quote(block: true)
  #set pagebreak(weak: true)

  #if title != none and title != "" {
    set heading(outlined: false)
    align(center)[
      = #title
      #preamble
    ]
  }

  #if include_line {
    align(center)[#line(
      length: 80%,
      stroke: main-color,
    )]

    v(0.3em)
  }


  #if include_outline {
    outline(title: none)
  }

  #if title_pagebreak {
    pagebreak()
  }

  #show heading.where(level: 1): it => {
    if (
      note_space and heading_page_break.get() and it.body != []
    ) {
      pagebreak(weak: true)
      it
    } else {
      it
    }
  }
  #show heading: set text(fill: main-color)

  #set heading(outlined: true, numbering: "1.")

  #set image(width: 30%)
  #show image: it => align(center)[
    #it
  ]

  #show table: it => align(center)[
    #it
  ]

  #show link: underline

  #doc

  #for i in range(blank_pages) {
    pagebreak()
  }
]

#let f = footnote


#let pattern_arrow = grid.cell(
  {
    set text(size: 3em)
    sym.arrow
  },
  align: horizon,
)

#let to-from(to, from) = {
  grid(
    columns: 3,
    gutter: 1em,
    align: horizon,
    to, pattern_arrow, from,
  )
}
