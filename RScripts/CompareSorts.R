######### Инициализация переменных##########
purple_colors <- c("#4A4063", "#685B7D", "#857696", "#BFACC8", "#C4B9D0", "#B29EC2", "#A083B3", "#8C61A1", "#783F8E", "#642980", "#4F1271")
rainbow_colors <- c("#4D9DE0", "#728BBD", "#97799A", "#BC6777", "#E15554", "#E1893F", "#E1BC29", "#8EB74E", "#3BB273", "#598D91", "#7768AE")
# GetCoolSorters
names_cool_sorters <- c("Heap", "Merge", "MergeRec", "Fast", "FastRec", "Standart")
# GetSortersVector
names_sorters <- c("Bubble", "Insert", "Selection", "Shell", "Heap", "Merge", "MergeRec", "Fast", "FastRec", "Standart")
names_some_distr <- c("Uniform 50 el.", "Uniform 500 el.", "Uniform 5000 el.", "Uniform 50000 el.", "Part.Ord. 50 el.", "Part.Ord 500 el.", "Part.Ord. 5000 el.", "Part.Ord 50000 el.")
names_radix_compare <- c("Normal int 5000", "Normal int 50000", "Normal int 500000")
main <- "НЕЗАДАННО!"
xlab <- "НЕЗАДАННО!"
ylab <- "Время:"
names_columns <- "НЕЗАДАННЫ!"
######### Считывание файла########
name <- "../data/hybryd_int" # без расширения
dat <- read.csv(paste(name, "csv", sep = "."), header = F, sep = " ")
dat <- t(dat)
  names_columns <- names_radix_compare
  main <- "Гибридная сортировка."
  xlab <- "Распределения."
#} else if (grepl("big_str", name)) {
#  names_columns <- names_cool_sorters
#  main <- "Cортировка 50000 строк. PartialMixing"
#  xlab <- "Хорошие сортировки"
#}
vec <- as.numeric(dat[, 1])
vec <- vec[1:length(vec)-1]


png(paste(name, "png", sep = "."), width = 1280, height = 720)
bar <- barplot(vec,
  border = 0, space = 0, xlab = xlab, ylab = ylab,
  main = main,
  col = rainbow_colors[1:length(vec)], font.lab = 2, font.main = 2, cex.main = 2, cex.lab = 1.5,
)
for (i in 1:length(names_columns)) {
  text(i - 0.5, par("usr")[3] - max(vec) * 0.03, srt = 15, adj = 0.5, labels = names_columns[i], xpd = TRUE, cex = 1, font = 2)
}
text(bar, vec, vec, pos = 3)
dev.off()
