
clf
for i = 1:numel(Xs)
    Color(i) = sqrt(Xs(i)^2+Ys(i)^2+Zs(i)^2);
end

scatter3(Xs, Ys, Zs, 100, Color, 'fill')
camproj('perspective')
ylim([0, 80])
xlim([-80, 0])
zlim([-12, 40])