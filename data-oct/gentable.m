result = zeros([5 3 4]);
cars = [50 100 200];
stime = [2 4 8 16 32];
captions = [["Average minimum queue time"], ["Average queue time"], ["Average maximum queue time"], ["Average throughput"]];
for j = [1:3]
  for i = [1:5]
    data = eval([alg, "_", num2str(stime(i)), "step_", num2str(cars(j)), "cars_500steps"])(300:500, :);
    dequeuetotal = sum(data(:, 3));
    # avg min
    result(i, j, 1) = mean(data(:, 4)(~isnan(data(:, 4))));
    # avg
    result(i, j, 2) = sum(data(:, 6)) / dequeuetotal;
    # avg max
    result(i, j, 3) =  mean(data(:, 5)(~isnan(data(:, 4))));
    # avg through
    result(i, j, 4) =  dequeuetotal / length(300:500);
  end
end

for i = [1:4]
  begintableline = ["\\begin{table}[Htb]\n\\centering\n\\begin{tabular}{cccc}\n\\hline\n\\textbf{cars} & 50 & 100 & 200\\\n\\hline\n\\textbf{switch time} & & & \\\\\n"];
  endtableline = ["\\hline\n\\end{tabular}\n\\caption{", captions(i), "}\n\\end{table}\n"];
  sprintf(begintableline)
  for j = [1:5]
    sprintf([num2str(stime(j)), " & ", num2str(result(j, 1, i)), " & ", num2str(result(j, 2, i)), " & ", num2str(result(j, 3, i)), " \\\\\n"])
  end
  sprintf(endtableline)
end