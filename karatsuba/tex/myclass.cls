\NeedsTeXFormat{LaTeX2e} % \NeedsTeXFormat{LaTeX2e} Specifies which version of LaTeX is required to use the class. Here ensures compatibility. LaTeX2e is the standard modern version.
\ProvidesClass{myclass}[2025/03/20 Custom Document Class] % \ProvidesClass{myclass}[<date> <description>] - Declares the name and version of your class file.

% Load a base class (article, report, etc.) and pass options
\LoadClass[12pt]{article} %\LoadClass[options]{baseclass}

% Customize packages
\RequirePackage{geometry}
\geometry{margin=1in}

\RequirePackage{amsmath}
\RequirePackage{graphicx}


% Customize section formatting, headers, etc.
\renewcommand{\section}{\@startsection{section}{1}{\z@}%
  {-3.5ex \@plus -1ex \@minus -.2ex}%
  {2.3ex \@plus.2ex}%
  {\normalfont\Large\bfseries}}

  % Set default title formatting
\renewcommand{\maketitle}{
   \begin{center}
     \Huge\bfseries \@title\\
     \large by \@author\\
     \today
   \end{center}
   \vspace{1cm}
 }
 
 % End of class file
 \endinput